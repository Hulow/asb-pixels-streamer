#include "CommandHandler.h"
#include "Logger.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* Should be a class ?*/
struct TaskArgs {
    CommandHandler handler;
    Command command;
    std::string msg;
};

void task(void* param) {
    auto* args = static_cast<TaskArgs*>(param);

    while(true) {
        args->handler.execute(args->command, [args]() {
            Logger logger;
            logger.info("MAIN", args->msg);
        });
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    delete args;
    vTaskDelete(NULL);
}


extern "C" void app_main() {
    Logger logger;
    CommandHandler handlerOne(logger);
    Command commandOne = Command::from(0, 255, 0, 10);
    CommandHandler handlerTwo(logger);
    Command commandTwo = Command::from(0, 255, 0, 20);

    auto* argsOne = new TaskArgs{
        handlerOne, 
        commandOne, 
        "Main one triggered"
    };

    auto* argsTwo = new TaskArgs{
        handlerTwo, 
        commandTwo, 
        "Main two triggered"
    };

    /* Check xTaskCreate */
    xTaskCreate(
        task,                 // Task function pointer
        "handlerOneTask",     // Name
        4096,                 // Stack size
        argsOne,              // Parameter
        5,                    // Priority
        NULL                  // Task handle
    );

    xTaskCreate(
        task,                 // Task function pointer
        "handlerTwoTask",     // Name
        4096,                 // Stack size
        argsTwo,              // Parameter
        5,                    // Priority
        NULL                  // Task handle
    );

    vTaskDelete(NULL);
}