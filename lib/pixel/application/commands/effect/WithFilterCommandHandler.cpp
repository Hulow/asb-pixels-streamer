#include "WithFilterCommandHandler.h"
#include "../CommandHandler.h"
#include "../../../core/Pixel.h"

WithFilterCommandHandler::WithFilterCommandHandler(IConsumer& consumer) : CommandHandler(consumer) {}

void WithFilterCommandHandler::execute(const Command& command, std::function<void()> callBack) {
    if (callBack) callBack();
}