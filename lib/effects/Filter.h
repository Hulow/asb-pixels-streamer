#pragma once

#include "../core/IConsumer.h"

class Filter : public IConsumer {
    protected:
        IConsumer& _consumer;

    public:
        Filter(IConsumer& consumer) : _consumer(consumer) {}

        virtual ~Filter() = default;

        virtual void enqueuePixel(Pixel& pixel) override = 0;

        virtual void start() override {
            _consumer.start();
        }
        
        virtual void signalLastPixel() override {
            _consumer.signalLastPixel();
        }

};