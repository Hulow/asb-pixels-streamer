#pragma once

#include "../core/IPixelConsumer.h"

class Filter : public IPixelConsumer {
    protected:
        IPixelConsumer& _consumer;

    public:
        Filter(IPixelConsumer& consumer) : _consumer(consumer) {}

        virtual ~Filter() = default;

        virtual void enqueuePixel(const Pixel& pixel) override = 0;

        virtual void start() override {
            _consumer.start();
        }
        
        virtual void signalLastPixel() override {
            _consumer.signalLastPixel();
        }

};