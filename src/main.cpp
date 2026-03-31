#include "driver/rmt_tx.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../lib/pixel/adapters/rmt/ConfigsBuilder.h"
#include "../lib/pixel/adapters/rmt/TimingBuilder.h"
#include "../lib/pixel/adapters/rmt/Transmitter.h"

#include "../lib/pixel/commands/effect/WithFilterCommandHandler.h"

#include "../lib/shared/adapters/Timer.h"
#include "../lib/shared/adapters/Task.h"

#include "../lib/pixel/adapters/effects/filters/Blackout.h"
#include "../lib/pixel/core/Pixel.h"

struct Params {
    ConfigsBuilder channelConfigs;
    Timing timingConfigs;
};

void runTaskOne(void* arg) {
    auto params = static_cast<Params*>(arg);
    Transmitter transmitter(
        params->channelConfigs.build(), 
        params->timingConfigs
    );

    int const LEDS_COUNT = 13;
    
    std::vector<Pixel> blackPixels;
    Pixel blackPixel = Pixel::from(0, 0, 0);

    std::vector<Pixel> redPixels;
    Pixel redPixel = Pixel::from(0, 255, 0);

    Timer timer;

    while (true) {
        blackPixels.clear();
        redPixels.clear();
 
        
        for (int i = 0; i < LEDS_COUNT; i++) {
            blackPixels.push_back(blackPixel);
        }

        transmitter.stream(blackPixels);

        for (int i = 0; i < LEDS_COUNT; i++) {
            redPixels.push_back(redPixel);
        }

        transmitter.stream(redPixels);

        timer.wait(1000); 
    }
}

extern "C" void app_main() {
    ConfigsBuilder baseConfigs = ConfigsBuilder()
        .clock(RMT_CLK_SRC_APB)
        .memBlockSymbols(256)
        .queueDepth(10)
        .resolutionHz(10 * 1000 * 1000);

    Timing timingConfigs = TimingBuilder()
        .highTimeSignal(800)
        .lowTimeSignal(300)
        .highTimeNoSignal(300)
        .lowTimeNoSignal(800)
        .resetTime(300000)
        .build();

    auto configsOne = baseConfigs.gpioNum(GPIO_NUM_5);
    Params* paramsOne = new Params{configsOne, timingConfigs};
    
    Task* taskOne = new Task(
        runTaskOne,
        "Blackout effect - channel 5",
        paramsOne
    );

    taskOne->start();

    auto configsTwo = baseConfigs.gpioNum(GPIO_NUM_4); // different GPIO
    Params* paramsTwo = new Params{configsTwo, timingConfigs};
    Task* taskTwo = new Task(
        runTaskOne, 
        "Color cycle - channel 4", 
        paramsTwo
    );

    taskTwo->start();
};