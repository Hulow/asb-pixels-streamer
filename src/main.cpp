#include "commands/CommandHandler.h"
#include "Logger.h"
#include "rmt.h"
#include "ConfigsBuilder.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string>
#include <sstream>

/* Task arguments */
struct TaskArgs {
    CommandHandler* handler;
    std::string msg;
};

/* Task function toggling two commands infinitely */
void task(void* param) {
    auto* args = static_cast<TaskArgs*>(param);

    Command cmdOff   = Command::from(0, 0, 0, 60);
    Command cmdGreen = Command::from(0, 255, 0, 60);

    std::function<void(bool)> executeNext;
    executeNext = [args, &executeNext, cmdOff, cmdGreen](bool isGreen) {
        Command current = isGreen ? cmdGreen : cmdOff;

        args->handler->execute(current, [args, &executeNext, isGreen]() {
            Logger logger;
            std::stringstream ss;
            ss << args->msg << " - " << (isGreen ? "Green" : "Off");
            logger.info("MAIN", ss.str());

            // Delay between toggles
            // vTaskDelay(pdMS_TO_TICKS(500));

            // Trigger opposite command
            executeNext(!isGreen);
        });
    };

    // Start with LEDs off
    executeNext(false);

    // Task itself just idles; callbacks handle toggling
    while (true) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    delete args;
    vTaskDelete(NULL);
}

extern "C" void app_main() {
    Logger logger;

    // Base configuration
    ConfigsBuilder baseConfigs = ConfigsBuilder()
        .clock(RMT_CLK_SRC_DEFAULT)
        .memBlockSymbols(128) // memory for LEDs
        .queueDepth(4)
        .resolutionHz(10'000'000);

    // First LED strip (GPIO4)
    ConfigsBuilder configsOne = baseConfigs.gpioNum(GPIO_NUM_4);
    auto* transceiverOne = new Rmt(configsOne.build());
    CommandHandler handlerOne(logger, *transceiverOne);
    auto* argsOne = new TaskArgs{ &handlerOne, "LED Strip 1" };

    // Second LED strip (GPIO5)
    ConfigsBuilder configsTwo = baseConfigs.gpioNum(GPIO_NUM_5);
    auto* transceiverTwo = new Rmt(configsTwo.build());
    CommandHandler handlerTwo(logger, *transceiverTwo);
    auto* argsTwo = new TaskArgs{ &handlerTwo, "LED Strip 2" };

    // Create FreeRTOS tasks
    xTaskCreate(task, "handlerOneTask", 4096, argsOne, 5, NULL);
    xTaskCreate(task, "handlerTwoTask", 4096, argsTwo, 5, NULL);

    // Main loop does nothing; tasks handle LEDs
    while (true) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    vTaskDelete(NULL);
}