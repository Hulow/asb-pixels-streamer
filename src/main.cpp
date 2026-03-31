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

    Transmitter transmitter(configsOne.build(), timingConfigs);

    int const LEDS_COUNT = 13;

    Pixel blackPixel = Pixel::from(0, 0, 0);
    Pixel redPixel = Pixel::from(0, 255, 0);

    std::vector<Pixel> blackPixels;
    for (int i = 0; i < LEDS_COUNT; i++) {
        blackPixels.push_back(blackPixel);
    }

    transmitter.stream(blackPixels);

    vTaskDelay(pdMS_TO_TICKS(10));  

    std::vector<Pixel> redPixels;
    for (int i = 0; i < LEDS_COUNT; i++) {
        redPixels.push_back(redPixel);
    }

    transmitter.stream(redPixels);

    vTaskDelay(pdMS_TO_TICKS(10));  

    transmitter.stream(blackPixels);

    vTaskDelay(pdMS_TO_TICKS(1000));  

    transmitter.stream(redPixels);




};