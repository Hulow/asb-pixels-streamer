#include "driver/rmt_tx.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../lib/drivers/rmt/ConfigsBuilder.h"
#include "../lib/drivers/rmt/TimingBuilder.h"
#include "../lib/drivers/rmt/Transmitter.h"

#include "../lib/commands/CommandHandler.h"
#include "../lib/commands/effect/WithFilterCommandHandler.h"

#include "../lib/effects/filters/Blackout.h"
#include "../lib/core/Pixel.h"

struct TaskParams {
    CommandHandler* handler;
    Command command;
};

void taskHandler(void* arg) {
    auto* params = static_cast<TaskParams*>(arg);

    while (true) {
        params->handler->execute(params->command, nullptr);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

extern "C" void app_main() {
    ConfigsBuilder baseConfigs = ConfigsBuilder()
        .clock(RMT_CLK_SRC_DEFAULT)
        .memBlockSymbols(192) 
        .queueDepth(10)
        .resolutionHz(10 * 1000 * 1000);

    Timing timingConfigs = TimingBuilder()
        .highTimeSignal(900)
        .lowTimeSignal(300)
        .highTimeNoSignal(300)
        .lowTimeNoSignal(900)
        .resetTime(60000)
        .build();
    
    int const STRIP_LENGTH = 1;
    Command command = Command::from(0, 255, 0, STRIP_LENGTH);
    
    auto configsOne = baseConfigs.gpioNum(GPIO_NUM_4);
    auto* transmitterOne = new Transmitter(configsOne.build(), timingConfigs);
    auto* blackoutFilterOne = new Blackout(*transmitterOne);
    auto* handlerOne = new WithFilterCommandHandler(*blackoutFilterOne);
    auto* taskOneParams = new TaskParams{ handlerOne, Command::from(0, 255, 0, 1) };

    auto configsTwo = baseConfigs.gpioNum(GPIO_NUM_5);
    auto* transmitterTwo = new Transmitter(configsTwo.build(), timingConfigs);
    auto* blackoutFilterTwo = new Blackout(*transmitterTwo);
    auto* handlerTwo = new WithFilterCommandHandler(*blackoutFilterTwo);
    auto* taskTwoParams = new TaskParams{ handlerTwo, Command::from(0, 0, 255, 1) };

    xTaskCreate(taskHandler, "Task One", 4096, taskOneParams, 5, nullptr);
    xTaskCreate(taskHandler, "Task Two", 4096, taskTwoParams, 5, nullptr);
};