#include "WithBehaviourCommandHandler.h"
#include "CommandHandler.h"
#include "Command.h"
#include <functional> 

WithBehaviourCommandHandler::WithBehaviourCommandHandler(Behaviour& consumer) : CommandHandler(consumer), _consumer(consumer) {}

void WithBehaviourCommandHandler::execute(const Command& command, std::function<void()> callBack) {
    Pixel pixel = Pixel::from(
        command.getGreen(), 
        command.getRed(), 
        command.getBlue()
    );
    
    for (int i = 1; i <= command.getPixelsCount(); i++) {}

    if (callBack) callBack();
}