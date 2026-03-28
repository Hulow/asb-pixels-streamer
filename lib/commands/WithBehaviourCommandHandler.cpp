#include "WithBehaviourCommandHandler.h"
#include "CommandHandler.h"
#include "Command.h"
#include <functional> 
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

    // int currentPixel;
    // int pixelsCount;
    // int chasingLength ;

WithBehaviourCommandHandler::WithBehaviourCommandHandler(Behaviour& consumer) : CommandHandler(consumer), _consumer(consumer) {}

void WithBehaviourCommandHandler::execute(const Command& command, std::function<void()> callBack) {
    // ESP_LOGI("HANDLER", "Pixel count: %d", command.getPixelsCount());
    // Pixel pixel = Pixel::from(
    //     command.getGreen(), 
    //     command.getRed(), 
    //     command.getBlue()
    // );
    
    for (int i = 1; i <= command.getPixelsCount(); i++) {
        Pixel pixel = Pixel::from(
            command.getGreen(), 
            command.getRed(), 
            command.getBlue()
        );
        // ESP_LOGI("HANDLER", "Starting Sequence %d", i);
        _consumer.setState({
            i,
            command.getPixelsCount(),
            1
        });
        _consumer.enqueuePixel(pixel);
        _consumer.signalLastPixel();
        // ESP_LOGI("HANDLER", "Reset signal sent");
    }

    _consumer.start();

    if (callBack) callBack();
}