#pragma once
#include <cstdint>
#include "Command.h"
#include <functional> 
#include "../ports/IPixelConsumer.h"

class CommandHandler {
    private:
        uint8_t _pixel;
        IPixelConsumer& _consumer;
    
    public:
        CommandHandler(IPixelConsumer& _consumer);
        void execute(const Command& command, std::function<void()> callBack);
};