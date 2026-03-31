#pragma once

#include <cstdint>
#include "Command.h"
#include <functional> 
#include "../ports/IConsumer.h"

class CommandHandler {
    protected:
        IConsumer& _consumer;
    
    public:
        CommandHandler(IConsumer& consumer) : _consumer(consumer) {};
        virtual ~CommandHandler() = default;
        virtual void execute(const Command& command, std::function<void()> callBack) = 0;
};