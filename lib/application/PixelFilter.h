#pragma once

#include "ports/IPixelConsumer.h"

class PixelFilter : public IPixelConsumer {
    protected:
        IPixelConsumer& _consumer;

    public:
        PixelFilter(IPixelConsumer& consumer) : _consumer(consumer) {}

        virtual ~PixelFilter() = default;

        virtual void enqueuePixel(const Pixel& pixel) override = 0;

        virtual void start() override {
            _consumer.start();
        }
        
        virtual void signalLastPixel() override {
            _consumer.signalLastPixel();
        }

};