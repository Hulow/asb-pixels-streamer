#pragma once

#include "../../shared/ITimer.h"
#include "../domain/IConsumer.h"
#include "Command.h"

class CommandHandler {
    private:
        IConsumer& _consumer;
        ITimer& _timer;
    public: 
        CommandHandler(IConsumer& consumer, ITimer& timer);
        void execute(const Command& command);
};