#pragma once

#include "WithBehaviourCommandHandler.h"
#include "CommandHandler.h"
#include "../core/IConsumer.h"

class WithBehaviourCommandHandler : public CommandHandler {
    public:
        WithBehaviourCommandHandler(IConsumer& consumer);
        void execute(const Command& command, std::function<void()> callBack) override;
};