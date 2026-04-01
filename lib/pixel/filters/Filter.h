#pragma once

#include "../../shared/ITimer.h"
#include "../domain/IConsumer.h"
#include "../domain/Frame.h"

class Filter : public IConsumer {
    protected:
        IConsumer& _consumer; 
        ITimer& _timer;
    public: 
        Filter(IConsumer& consumer, ITimer& timer) : _consumer(consumer), _timer(timer) {}
        
        virtual ~Filter() = default;

        virtual void stream(Frame& frame) = 0;
};