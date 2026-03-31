#include "CommandHandler.h"
#include "../../application/domain/Pixel.h"

CommandHandler::CommandHandler(IConsumer& consumer) : _consumer(consumer) {}

void CommandHandler::execute(
    const Command& command, 
    std::function<void()> callBack
) {
    if (callBack) callBack();
}