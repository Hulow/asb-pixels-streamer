#pragma once

#include "CommandHandler.h"

class WithFilterCommandHandler : public CommandHandler {
    public: 
        WithFilterCommandHandler(IConsumer& consumer);
        void execute(const Command& command, std::function<void()> callBack) override;
};