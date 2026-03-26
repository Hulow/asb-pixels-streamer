#include "../lib/commands/CommandHandler.h"
#include "../adapters/PixelWaveformPipeline.h"
#include "ConfigsBuilder.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string>
#include <atomic>
#include "../lib/effects/Brightness.h"

/* Global stop flag */
std::atomic<bool> stopTasks(false);

/* Task arguments for both strips */
struct DualTaskArgs {
    CommandHandler* handlerOne;
    CommandHandler* handlerTwo;
    std::string msgOne;
    std::string msgTwo;
};

/* Task function controlling both LED strips in sync */
void taskBothStrips(void* param) {
    auto* args = static_cast<DualTaskArgs*>(param);

    Command cmdOff   = Command::from(0, 255, 0, 60);
    Command cmdGreen = Command::from(0, 220, 0, 60);

    bool isGreen = false;

    while (!stopTasks.load()) {
        Command current = isGreen ? cmdGreen : cmdOff;

        // Send command to both strips
        args->handlerOne->execute(current, nullptr);
        args->handlerTwo->execute(current, nullptr);

        isGreen = !isGreen;

        // Delay between toggles
        // vTaskDelay(pdMS_TO_TICKS(10000));
    }

    // Ensure both LED strips are completely off before exiting
    args->handlerOne->execute(cmdOff, nullptr);
    args->handlerTwo->execute(cmdOff, nullptr);

    delete args;
    vTaskDelete(NULL);
}

extern "C" void app_main() {
    // Base configuration
    ChannelConfigsBuilder baseConfigs = ChannelConfigsBuilder()
        .clock(RMT_CLK_SRC_DEFAULT)
        .memBlockSymbols(128)
        .queueDepth(4)
        .resolutionHz(10'000'000);
    
    static constexpr PixelTiming ws2815Timing{
        .highTimeSignal   = 300,
        .lowTimeSignal    = 1090,
        .highTimeNoSignal = 1090,
        .lowTimeNoSignal  = 320
    };

    // First LED strip (GPIO4)
    auto configsOne = baseConfigs.gpioNum(GPIO_NUM_4);
    auto* transceiverOne = new PixelWaveFormPipeline(configsOne, ws2815Timing);
    auto* bright = new Brightness(*transceiverOne, 0.92f);
    auto* handlerOne = new CommandHandler(*bright);

    // // Second LED strip (GPIO5)
    auto configsTwo = baseConfigs.gpioNum(GPIO_NUM_5);
    auto* transceiverTwo = new PixelWaveFormPipeline(configsTwo, ws2815Timing);
    auto* handlerTwo = new CommandHandler(*transceiverTwo);

    // Prepare task arguments
    auto* dualArgs = new DualTaskArgs{
        handlerOne,
        handlerTwo,
        "LED Strip 1",
        "LED Strip 2"
    };

    // Create a single FreeRTOS task for both strips
    xTaskCreate(
        taskBothStrips,  // Task function
        "DualStripTask", // Task name
        4096,            // Stack size
        dualArgs,        // Parameter
        5,               // Priority
        NULL             // Task handle
    );

    vTaskDelete(NULL);
}