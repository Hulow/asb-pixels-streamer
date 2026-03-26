#pragma once
#include <cstdint>
#include "Command.h"
#include <functional> 
#include "../ports/IPixelStreamer.h"

class CommandHandler {
    private:
        uint8_t _pixel;
        IPixelsStreamer& _streamer;
    
    public:
        CommandHandler(IPixelsStreamer& streamer);
        void execute(const Command& command, std::function<void()> callBack);
};