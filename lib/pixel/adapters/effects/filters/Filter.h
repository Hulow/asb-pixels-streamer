#pragma once

#include "../../../../shared/ports/ITimer.h"
#include "../../../application/ports/IConsumer.h"
#include "../../../application/domain/Frame.h"


class Filter : public IConsumer {
    protected:
        IConsumer& _consumer;
        ITimer& _timer;
    public:
        Filter(IConsumer& consumer, ITimer& timer) : _consumer(consumer), _timer(timer) {}

        virtual ~Filter() = default;

        virtual void stream(Frame& frame) = 0;
};