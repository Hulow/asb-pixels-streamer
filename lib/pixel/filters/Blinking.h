#pragma once

#include "Filter.h"
#include "../domain/Pixel.h"

class Blinking : public Filter {
    private:
        bool _state = true;
        Pixel _pixelOff = Pixel::from(0, 0, 0);
    public:
        Blinking(IConsumer& consumer) : Filter(consumer) {}
        void stream(Frame& frame) override {
            _state = !_state; // toggle on/off per frame

            if (!_state) {
                // turn off all pixels
                for (auto& pixel : frame.getPixels()) {
                    pixel = Pixel::from(0, 0, 0);
                }
            }

            _consumer.stream(frame); // send to transmitter
        }
};