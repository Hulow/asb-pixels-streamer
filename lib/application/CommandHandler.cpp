#include "CommandHandler.h"
#include "Logger.h"
#include <sstream>

CommandHandler::CommandHandler(Logger& logger) : _logger(logger) {}

void CommandHandler::execute(const Command& command, std::function<void()> callBack) {
    std::stringstream ss;
    ss << "Executed with pixel: " << static_cast<int>(command.getPixel());
    _logger.info("CommandHandler", ss.str());

    callBack();
}