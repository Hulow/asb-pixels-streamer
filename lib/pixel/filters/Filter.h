#pragma once

#include "../domain/IConsumer.h"
#include "../domain/Frame.h"

class Filter : public IConsumer {
    protected:
        IConsumer& _consumer; 
    public: 
        Filter(IConsumer& consumer) : _consumer(consumer) {}
        
        virtual ~Filter() = default;

        virtual void stream(Frame& frame) = 0;
};