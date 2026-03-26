#pragma once

#include "../core/IPixelConsumer.h"

class Behaviour : public IPixelConsumer {
    protected:
        IPixelConsumer& _consumer; 
    public: 
        Behaviour(IPixelConsumer& consumer) : _consumer(consumer) {}
        virtual ~Behaviour() = default;
        virtual void enqueuePixel(const Pixel& pixel) override = 0;
        virtual void start() override {
            _consumer.start();
        }
        virtual void signalLastPixel() override {
            _consumer.signalLastPixel();
        }

};