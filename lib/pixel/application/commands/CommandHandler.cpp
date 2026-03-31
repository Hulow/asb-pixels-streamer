#include "CommandHandler.h"
#include "../../application/domain/Pixel.h"

CommandHandler::CommandHandler(IConsumer& consumer, ITimer& timer) : _consumer(consumer), _timer(timer) {}

void CommandHandler::execute(
    const Command& command, 
    std::function<void()> callBack
) {
    if (callBack) callBack();
}