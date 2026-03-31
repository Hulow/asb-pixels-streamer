#pragma once

#include <functional> 

#include "Command.h"
#include "../ports/IConsumer.h"

class CommandHandler {
    private:
        IConsumer& _consumer;
    public: 
        CommandHandler(IConsumer& consumer);
        void execute(const Command& command, std::function<void()> callBack);
};