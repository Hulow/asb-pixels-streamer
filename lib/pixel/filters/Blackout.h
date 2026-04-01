#pragma once

#include "Filter.h"
#include "../domain/IConsumer.h"
#include "../domain/Frame.h"

class Blackout : public Filter {
    public:
        Blackout(IConsumer& consumer, ITimer& timer) : Filter(consumer, timer) {}
        void stream(Frame& frame) override {
            for (auto& pixel : frame.getPixels()) {
                pixel.turnOff();

            };

            _consumer.stream(frame);
            _timer.wait(100);
        }
};