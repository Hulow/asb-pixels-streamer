#pragma once

#include "../../../shared/ports/ITimer.h"
#include "../ports/IConsumer.h"
#include "Command.h"

class CommandHandler {
    private:
        IConsumer& _consumer;
    public: 
        CommandHandler(IConsumer& consumer);
        void execute(const Command& command);
};