#pragma once

#include "Filter.h"
#include "../../core/IConsumer.h"

class Blackout : public Filter {
    public:
        Blackout(IConsumer& consumer) : Filter(consumer) {}
        void pushPixel(Pixel& pixel) override {
            pixel.turnOff();
            return _consumer.pushPixel(pixel);
        }
};