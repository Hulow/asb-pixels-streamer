#include "WithBehaviourCommandHandler.h"
#include "CommandHandler.h"
#include "Command.h"
#include <functional> 

WithBehaviourCommandHandler::WithBehaviourCommandHandler(IConsumer& consumer) : CommandHandler(consumer) {}

void WithBehaviourCommandHandler::execute(const Command& command, std::function<void()> callBack) {
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