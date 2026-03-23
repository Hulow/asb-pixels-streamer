#pragma once
#include <cstdint>
#include "Command.h"
#include "Logger.h"
#include <functional> 
#include "../ports/IPixelStreamer.h"

class CommandHandler {
    private:
        uint8_t _pixel;
        Logger& _logger;
        IPixelsStreamer& _streamer;
    
    public:
        CommandHandler(Logger& logger, IPixelsStreamer& streamer);
        void execute(const Command& command, std::function<void()> callBack);
};