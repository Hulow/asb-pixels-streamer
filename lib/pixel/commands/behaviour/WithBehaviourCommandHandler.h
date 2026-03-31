#pragma once

#include "WithBehaviourCommandHandler.h"
#include "../CommandHandler.h"
#include "../../core/IConsumer.h"
#include "../../effects/behaviour/Behaviour.h"

class WithBehaviourCommandHandler : public CommandHandler {
    private:
        Behaviour& _consumer;
    public:
        WithBehaviourCommandHandler(Behaviour& consumer);
        void execute(const Command& command, std::function<void()> callBack) override;
};