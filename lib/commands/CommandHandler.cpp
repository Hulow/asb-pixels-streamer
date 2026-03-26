#include "CommandHandler.h"
#include "../core/Pixel.h"

CommandHandler::CommandHandler(IConsumer& consumer) : _consumer(consumer) {}

void CommandHandler::execute(const Command& command, std::function<void()> callBack) {
    for (int i = 0; i < command.getPixelsCount(); ++i) {
           _consumer.enqueuePixel(
            Pixel::from(
                command.getGreen(), 
                command.getRed(), 
                command.getBlue()
            )
        );
    }
     
    _consumer.signalLastPixel();
    _consumer.start();

    if (callBack) callBack();
}