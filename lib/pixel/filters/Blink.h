#pragma once

#include "Filter.h"

class Blink : public Filter {
    public:
        Blink(IConsumer& consumer) : Filter(consumer) {}
        void stream(Frame& frame) override {
            _consumer.stream(frame);
            for (auto& pixel : frame.getPixels()) {
                pixel.turnOff();
            };
            _consumer.stream(frame);
        }
};