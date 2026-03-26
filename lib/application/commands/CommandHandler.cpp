#include "CommandHandler.h"
#include "domain/Pixel.h"

CommandHandler::CommandHandler(IPixelConsumer& consumer) : _consumer(consumer) {}

void CommandHandler::execute(const Command& command, std::function<void()> callBack) {
    for (int i = 0; i < command.getPixelsCount(); ++i) {
    }

    if (callBack) callBack();
}