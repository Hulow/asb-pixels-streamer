#include "CommandHandler.h"
#include "Logger.h"
static const char* TAG = "CommandHandler";
#include <sstream>

CommandHandler::CommandHandler(Logger& logger) : _logger(logger) {}

void CommandHandler::execute(const Command& command) {
    std::stringstream ss;
    ss << "Executing command on pixel " << static_cast<int>(command.getPixel());
    _logger.info(TAG, ss.str());
}