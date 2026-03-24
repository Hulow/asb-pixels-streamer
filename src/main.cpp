#include "commands/CommandHandler.h"
#include "Logger.h"
#include "Transceiver.h"
#include "ConfigsBuilder.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* Should be a class ?*/
struct TaskArgs {
    CommandHandler handler;
    Command command;
    std::string msg;
};

void task(void* param) {
    auto* args = static_cast<TaskArgs*>(param);

    // while(true) {
        args->handler.execute(args->command, [args]() {
            Logger logger;
            logger.info("MAIN", args->msg);
        });
        vTaskDelay(pdMS_TO_TICKS(1000));
    // }

    delete args;
    vTaskDelete(NULL);
}


extern "C" void app_main() {
    Logger logger;
    ConfigsBuilder baseConfigs = ConfigsBuilder()
        .clock(static_cast<rmt_clock_source_t>(RMT_CLK_SRC_DEFAULT))
        .memBlocks(64)
        .queueDepth(1)
        .resolutionHz(10'000'000);

    ConfigsBuilder configsOne = baseConfigs.gpioNum(GPIO_NUM_4);
    Transceiver transceiverOne(configsOne.build());
    CommandHandler handlerOne(logger, transceiverOne);
    Command commandOne = Command::from(0, 0, 0, 10);

    ConfigsBuilder configsTwo = baseConfigs.gpioNum(GPIO_NUM_5);
    Transceiver transceiverTwo(configsTwo.build());
    CommandHandler handlerTwo(logger, transceiverTwo);
    Command commandTwo = Command::from(0, 255, 0, 20);

    auto* argsOne = new TaskArgs{
        handlerOne, 
        commandOne, 
        "Main one triggered"
    };

    auto* argsTwo = new TaskArgs{
        handlerTwo, 
        commandTwo, 
        "Main two triggered"
    };

    /* Check xTaskCreate */
    xTaskCreate(
        task,                 // Task function pointer
        "handlerOneTask",     // Name
        4096,                 // Stack size
        argsOne,              // Parameter
        5,                    // Priority
        NULL                  // Task handle
    );

    // xTaskCreate(
    //     task,                 // Task function pointer
    //     "handlerTwoTask",     // Name
    //     4096,                 // Stack size
    //     argsTwo,              // Parameter
    //     5,                    // Priority
    //     NULL                  // Task handle
    // );

    vTaskDelete(NULL);
}