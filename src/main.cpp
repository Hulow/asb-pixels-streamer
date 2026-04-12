#include "driver/rmt_tx.h"

#include "../lib/shared/Timer.h"

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

    Timer timer;

    /* ---- CHANNEL 5 ---- */

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

    /* ---- Start WIFI Network ---- */

    WifiManager wifiManager;
    wifiManager.start();

    /* ---- Start Web Server ---- */

    std::vector<IRoute*> routes = {
        &route
    };

    WebServer webServer(routes);
    webServer.start();
    webServer.registerRoutes();

     while (true) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}