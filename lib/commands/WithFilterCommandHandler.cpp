#include "WithFilterCommandHandler.h"
#include "CommandHandler.h"
#include "../core/Pixel.h"

WithFilterCommandHandler::WithFilterCommandHandler(IConsumer& consumer) : CommandHandler(consumer) {}

void WithFilterCommandHandler::execute(const Command& command, std::function<void()> callBack) {
    Pixel pixel = Pixel::from(
        command.getGreen(), 
        command.getRed(), 
        command.getBlue()
    );
    for (int i = 0; i < command.getPixelsCount(); ++i) {
        _consumer.enqueuePixel(pixel);
    }
    _consumer.signalLastPixel();
    _consumer.start();

    if (callBack) callBack();
}