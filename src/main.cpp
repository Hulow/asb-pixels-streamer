#include "driver/rmt_tx.h"

#include "../lib/drivers/rmt/ConfigsBuilder.h"
#include "../lib/drivers/rmt/TimingBuilder.h"
#include "../lib/drivers/rmt/Transmitter.h"
#include "../lib/core/Pixel.h"

extern "C" void app_main() {
    ConfigsBuilder baseConfigs = ConfigsBuilder()
        .clock(RMT_CLK_SRC_DEFAULT)
        .memBlockSymbols(384) // you devide by the 24 bits (+ resets) you have the number of leds (step of 64)
        .queueDepth(10)
        .resolutionHz(10 * 1000 * 1000);

    Timing timingConfigs = TimingBuilder()
        .highTimeSignal(900)
        .lowTimeSignal(300)
        .highTimeNoSignal(300)
        .lowTimeNoSignal(900)
        .resetTime(60000)
        .build();
    
    auto configsOne = baseConfigs.gpioNum(GPIO_NUM_5);
    Transmitter transmitter(configsOne.build(), timingConfigs);

    Pixel red = Pixel::from(0,255,0);
    Pixel black = Pixel::from(0,0,0);

    for (int i = 0; i < 1; i++) {
        transmitter.pushPixel(red);
    }
    transmitter.pushResetSignal();

    for (int i = 0; i < 2; i++) {
        transmitter.pushPixel(red);
    }
    transmitter.pushResetSignal();

    for (int i = 0; i < 3; i++) {
        transmitter.pushPixel(red);
    }
    transmitter.pushResetSignal();

    for (int i = 0; i < 4; i++) {
        transmitter.pushPixel(red);
    }
    transmitter.pushResetSignal();

    transmitter.start();

    transmitter.printQueue();
};