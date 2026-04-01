#pragma once

#include "Filter.h"
#include "../../../application/ports/IConsumer.h"
#include "../../../application/domain/Frame.h"

class Blackout : public Filter {
    public:
        Blackout(IConsumer& consumer, ITimer& timer) : Filter(consumer, timer) {}
        void stream(Frame& frame) {
            for (auto& pixel : frame.getPixels()) {
                pixel.turnOff();
                _consumer.stream(frame);
                _timer.wait(100);
            };
        }
};