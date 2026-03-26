#pragma once
#include <cstdint>
#include "Command.h"
#include <functional> 
#include "../core/IConsumer.h"

class CommandHandler {
    private:
        uint8_t _pixel;
        IConsumer& _consumer;
    
    public:
        CommandHandler(IConsumer& _consumer);
        void execute(const Command& command, std::function<void()> callBack);
};