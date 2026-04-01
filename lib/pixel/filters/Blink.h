#pragma once

#include "Filter.h"
#include "../domain/IConsumer.h"
#include "../domain/Frame.h"

class Blink : public Filter {
    public:
        Blink(IConsumer& consumer, ITimer& timer) : Filter(consumer, timer) {}
        void stream(Frame& frame) override {
            _consumer.stream(frame);
            _timer.wait(50);
            for (auto& pixel : frame.getPixels()) {
                pixel.turnOff();
            };
            _consumer.stream(frame);
        }
};