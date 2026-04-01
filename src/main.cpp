#include "driver/rmt_tx.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../lib/shared/Timer.h"
#include "../lib/shared/Task.h"

#include "../lib/pixel/drivers/ConfigsBuilder.h"
#include "../lib/pixel/drivers/TimingBuilder.h"
#include "../lib/pixel/drivers/rmt/Transmitter.h"
#include "../lib/pixel/filters/Blackout.h"
#include "../lib/pixel/filters/Sparkling.h"

#include "../lib/pixel/commands/CommandHandler.h"
#include "../lib/pixel/commands/Command.h"

#include "../lib/pixel/domain/Pixel.h"

struct Params {
    ConfigsBuilder channelConfigs;
    Timing timingConfigs;
};

void runTask(void* arg) {
    int const LEDS_COUNT = 60;
    Command commandOn = Command::from(
        0, 
        255, 
        0, 
        LEDS_COUNT
    );

    Command commandOff = Command::from(
        0,
        0,
        0,
        LEDS_COUNT
    );

    auto params = static_cast<Params*>(arg);
    Transmitter transmitter(
        params->channelConfigs.build(), 
        params->timingConfigs
    );

    Timer timer;
    Blackout blackoutEffect(transmitter, timer);
    CommandHandler handlerOne(blackoutEffect);

    Sparkling sparklingEffect(transmitter, timer);
    CommandHandler handlerTwo(sparklingEffect);

     while (true) {
        handlerOne.execute(commandOn);
        timer.wait(100);

        handlerTwo.execute(commandOn);
        timer.wait(100);
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
        .lowTimeSignal(450)
        .highTimeNoSignal(400)
        .lowTimeNoSignal(850)
        .resetTime(400000)
        .build();

    auto configsOne = baseConfigs.gpioNum(GPIO_NUM_5);
    Params* paramsOne = new Params{configsOne, timingConfigs};
    Task* taskOne = new Task(
        runTask,
        "Blackout effect - channel 5",
        paramsOne
    );

    taskOne->start();

    auto configsTwo = baseConfigs.gpioNum(GPIO_NUM_4);
    Params* paramsTwo = new Params{configsTwo, timingConfigs};
    Task* taskTwo = new Task(
        runTask, 
        "Color cycle - channel 4", 
        paramsTwo
    );

    taskTwo->start();
};