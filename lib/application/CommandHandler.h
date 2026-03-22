#pragma once
#include <cstdint>
#include "Command.h"
#include "Logger.h"

class CommandHandler {
    private:
        uint8_t _pixel;
        Logger& _logger;
    
    public:
        CommandHandler(Logger& logger);
        void execute(const Command& command);
};