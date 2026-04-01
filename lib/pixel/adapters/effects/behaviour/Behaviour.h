#pragma once

#include <vector>

#include "../../../../shared/ports/ITimer.h"
#include "../../../application/ports/IConsumer.h"
#include "../../../application/domain/Frame.h"


class Behaviour : public IConsumer {
    protected:
        IConsumer& _consumer; 
        ITimer& _timer;
    public: 
        Behaviour(IConsumer& consumer, ITimer& timer) : _consumer(consumer), _timer(timer) {}
        
        virtual ~Behaviour() = default;

        virtual void stream(Frame& frame) = 0;
};