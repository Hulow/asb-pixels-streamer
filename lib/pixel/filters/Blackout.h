#pragma once

#include "Filter.h"

class Blackout : public Filter {
    public:
        Blackout(IConsumer& consumer) : Filter(consumer) {}
        void stream(Frame& frame) override {
            for (auto& pixel : frame.getPixels()) {
                pixel.turnOff();

            };

            _consumer.stream(frame);
        }
};