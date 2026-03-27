#pragma once

#include "../effects/Filter.h"
#include "../core/IConsumer.h"

class Blackout : public Filter {
    public:
        Blackout(IConsumer& consumer) : Filter(consumer) {}
        void enqueuePixel(Pixel& pixel) override {
            pixel.turnOff();
            return _consumer.enqueuePixel(pixel);
        }
};