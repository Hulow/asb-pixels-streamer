#include "WithBehaviourCommandHandler.h"
#include "../CommandHandler.h"
#include "../Command.h"
#include <functional> 

WithBehaviourCommandHandler::WithBehaviourCommandHandler(Behaviour& consumer) : CommandHandler(consumer), _consumer(consumer) {}

void WithBehaviourCommandHandler::execute(const Command& command, std::function<void()> callBack) {
    if (callBack) callBack();
}