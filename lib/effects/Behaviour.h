#pragma once

#include "../core/IConsumer.h"

class Behaviour : public IConsumer {
    protected:
        IConsumer& _consumer; 
    public: 
        Behaviour(IConsumer& consumer) : _consumer(consumer) {}
        virtual ~Behaviour() = default;
        virtual void enqueuePixel(Pixel& pixel) = 0;
        virtual void start() override {
            _consumer.start();
        }
        virtual void signalLastPixel() override {
            _consumer.signalLastPixel();
        }
};