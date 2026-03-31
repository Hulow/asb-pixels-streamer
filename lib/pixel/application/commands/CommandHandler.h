#pragma once

#include <functional> 

#include "../../../shared/ports/ITimer.h"
#include "../ports/IConsumer.h"
#include "Command.h"

class CommandHandler {
    private:
        IConsumer& _consumer;
        ITimer& _timer;
    public: 
        CommandHandler(IConsumer& consumer, ITimer& timer);
        void execute(const Command& command, std::function<void()> callBack);
};