#include "CommandHandler.h"
#include "Logger.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern "C" void app_main() {
    Logger logger;
    CommandHandler handler(logger);
    handler.execute(Command::from(10));
}
