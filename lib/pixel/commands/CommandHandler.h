#pragma once

#include "../../shared/ITimer.h"
#include "../domain/IConsumer.h"
#include "Command.h"

class CommandHandler {
    private:
        IConsumer& _consumer;
    public: 
        CommandHandler(IConsumer& consumer);
        void execute(const Command& command);
};