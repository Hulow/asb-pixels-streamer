#include "driver/rmt_tx.h"

#include "../lib/shared/Timer.h"
#include "../lib/shared/TaskScheduler.h"

#include "../lib/pixel/drivers/ConfigsBuilder.h"
#include "../lib/pixel/drivers/TimingBuilder.h"
#include "../lib/pixel/drivers/rmt/Transmitter.h"

#include "../lib/pixel/filters/Blinking.h"
#include "../lib/pixel/filters/Chasing.h"
#include "../lib/pixel/filters/Fading.h"

#include "../lib/pixel/commands/CommandHandler.h"
#include "../lib/pixel/commands/Command.h"

#include "../lib/wifi/WifiManager.h"
#include "../lib/http/WebServer.h"

#include "../lib/pixel/web/ChasingRoute.h"
#include "../lib/pixel/web/ChasingController.h"
#include "../lib/pixel/services/ChasingService.h"


struct Params {
    CommandHandler* handler;
    Command command;
};

void runTask(void* arg) {
    auto params = static_cast<Params*>(arg);
    params->handler->execute(params->command);
}

extern "C" void app_main() {
    WifiManager wifiManager;
    wifiManager.start();
    
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

    const int LEDS_COUNT = 13;
    Command command = Command::from(0, 255, 0, LEDS_COUNT);
    Timer timer;

    /* ---- CHANNEL 1 ---- */
    // Transmitter* transmitterOne = new Transmitter(
    //     baseConfigs.gpioNum(GPIO_NUM_5).build(), 
    //     timingConfigs
    // );
    // Blinking* blinkingEffectOne = new Blinking(*transmitterOne);
    // Chasing* chasingOne = new Chasing(*blinkingEffectOne);
    // CommandHandler* handlerOne = new CommandHandler(
    //     *chasingOne, 
    //     *timer
    // );
     Transmitter transmitterOne(
        baseConfigs.gpioNum(GPIO_NUM_5).build(), 
        timingConfigs
    );
    Blinking blinkingEffectOne(transmitterOne);
    Chasing chasingOne(blinkingEffectOne);
    CommandHandler handlerOne(
        chasingOne, 
        timer
    );

    ChasingService service(handlerOne, "service");
    ChasingController controller(service);
    ChasingRoute route(controller);

    std::vector<IRoute*> routes = {
        &route
    };

    WebServer webServer(routes);
    webServer.start();
    webServer.registerRoutes();


    // Params* paramsOne = new Params{
    //     handlerOne, 
    //     command
    // };

    // TaskScheduler* task1 = new TaskScheduler(
    //     runTask, 
    //     "Handler on channel 5", 
    //     paramsOne
    // );
    // task1->start();

    // /* ---- CHANNEL 2 ---- */
    // Transmitter* transmitterTwo = new Transmitter(
    //     baseConfigs.gpioNum(GPIO_NUM_4).build(), 
    //     timingConfigs
    // );

    // /* Wrap in Fading */
    // Fading* fadingEffect = new Fading(*transmitterTwo);

    // /* Wrap in Chasing */
    // Chasing* chasingEffect = new Chasing(*fadingEffect);

    // /* Wrap in Blinking */
    // Blinking* blinkingEffectTwo = new Blinking(*chasingEffect);

    // /* Use the chain in command handler */
    // CommandHandler* handlerTwo = new CommandHandler(*blinkingEffectTwo, *timer);

    // Params* params2 = new Params{
    //     handlerTwo, 
    //     command
    // };
    // TaskScheduler* task2 = new TaskScheduler(
    //     runTask, 
    //     "Handler on channel 4", 
    //     params2
    // );
    // task2->start();

     while (true) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}