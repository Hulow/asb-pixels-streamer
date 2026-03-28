#include "driver/rmt_tx.h"

#include "../lib/drivers/rmt/ConfigsBuilder.h"
#include "../lib/drivers/rmt/TimingBuilder.h"
#include "../lib/drivers/rmt/Transmitter.h"
#include "../lib/core/Pixel.h"

extern "C" void app_main() {
    ConfigsBuilder baseConfigs = ConfigsBuilder()
        .clock(RMT_CLK_SRC_DEFAULT)
        .memBlockSymbols(128)
        .queueDepth(10)
        .resolutionHz(10 * 1000 * 1000);

    Timing timingConfigs = TimingBuilder()
        .highTimeSignal(300)
        .lowTimeSignal(1090)
        .highTimeNoSignal(1090)
        .lowTimeNoSignal(320)
        .resetTime(3000000)
        .build();
    
    auto configsOne = baseConfigs.gpioNum(GPIO_NUM_5);
    Transmitter transmitter(configsOne.build(), timingConfigs);

    Pixel red = Pixel::from(0,255,0);
    Pixel black = Pixel::from(0,0,0);

    //frame 1
    transmitter.pushPixel(red);
    transmitter.pushResetSignal();
    //frame 2
    transmitter.pushPixel(red);
    transmitter.pushPixel(red);
    transmitter.pushResetSignal();
    
    transmitter.printQueue();
    transmitter.start();
};