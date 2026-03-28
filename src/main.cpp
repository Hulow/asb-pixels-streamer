#include "ConfigsBuilder.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string>
#include <atomic>
#include "esp_log.h"

#include "../adapters/PixelWaveformPipeline.h"

#include "../lib/commands/CommandHandler.h"
#include "../lib/commands/WithFilterCommandHandler.h"
#include "../lib/commands/WithBehaviourCommandHandler.h"

#include "../lib/effects/Brightness.h"
#include "../lib/effects/Chasing.h"
#include "../lib/effects/Blackout.h"

/* Global stop flag */
std::atomic<bool> stopTasks(false);

/* Task arguments for both strips */
struct DualTaskArgs {
    // CommandHandler* handlerOne;
    CommandHandler* handlerTwo;
    // std::string msgOne;
    std::string msgTwo;
};

/* Task function controlling both LED strips in sync */
void taskBothStrips(void* param) {
    auto* args = static_cast<DualTaskArgs*>(param);

    Command backCommand   = Command::from(0, 255, 0, 3);
    Command greenCommand = Command::from(0, 0, 0, 3);

    bool isGreen = false;

    while (!stopTasks.load()) {
        Command current = isGreen ? backCommand : greenCommand;

        // Send command to both strips
        // args->handlerOne->execute(current, nullptr);
        args->handlerTwo->execute(current, nullptr);

        // ESP_LOGI("MAIN", "HANDLER DONE");

        isGreen = !isGreen;

        // Delay between toggles mardi 3, vendredi 1
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    // Ensure both LED strips are completely off before exiting
    // args->handlerOne->execute(greenCommandOne, nullptr);
    // args->handlerTwo->execute(greenCommandTwo, nullptr);

    delete args;
    vTaskDelete(NULL);
}

extern "C" void app_main() {
    // Base configuration
    ChannelConfigsBuilder baseConfigs = ChannelConfigsBuilder()
        .clock(RMT_CLK_SRC_DEFAULT)
        .memBlockSymbols(128)
        .queueDepth(10)
        .resolutionHz(80 * 1000 * 1000);
    
    static constexpr PixelTiming ws2815Timing{
        .highTimeSignal   = 300,
        .lowTimeSignal    = 1090,
        .highTimeNoSignal = 1090,
        .lowTimeNoSignal  = 320
    };

    //RESET
    auto configsOne = baseConfigs.gpioNum(GPIO_NUM_5);
    auto* transceiverOne = new PixelWaveFormPipeline(configsOne, ws2815Timing);

    auto configsTwo = baseConfigs.gpioNum(GPIO_NUM_4);
    auto* transceiverTwo = new PixelWaveFormPipeline(configsTwo, ws2815Timing);

    Command commandOff   = Command::from(0, 0, 0, 10);

    Blackout blackoutOne(*transceiverOne);
    WithFilterCommandHandler handlerOneReset(blackoutOne);
    handlerOneReset.execute(commandOff, nullptr);

    Blackout blackoutTwo(*transceiverTwo);
    WithFilterCommandHandler handlerTwoReset(blackoutTwo);
    handlerTwoReset.execute(commandOff, nullptr);

    Command command = Command::from(0, 255, 0, 60);

    // //INIT
    auto* brightEffect = new Brightness(*transceiverOne, 0.92f);
    auto* handlerOne = new WithFilterCommandHandler(*brightEffect);
    handlerOne->execute(command, nullptr);

    
    vTaskDelay(pdMS_TO_TICKS(10));

    // auto* chasingEffect = new Chasing(*transceiverTwo);
    // auto* handlerTwo = new WithBehaviourCommandHandler(*chasingEffect);
    // handlerTwo->execute(command, nullptr);

    
    // // Prepare task arguments
    // auto* dualArgs = new DualTaskArgs{
    //     // handlerOne,
    //     handlerTwo,
    //     // "LED Strip 1",
    //     "LED Strip 2"
    // };

    // // Create a single FreeRTOS task for both strips
    // xTaskCreate(
    //     taskBothStrips,  // Task function
    //     "DualStripTask", // Task name
    //     4096,            // Stack size
    //     dualArgs,        // Parameter
    //     5,               // Priority
    //     NULL             // Task handle
    // );

    // vTaskDelete(NULL);
};