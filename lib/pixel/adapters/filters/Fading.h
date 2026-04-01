#pragma once

#include "Filter.h"
#include "../../application/ports/IConsumer.h"
#include "../../application/domain/Frame.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class Fading : public Filter {
    private:
        float _factor;
    
    public:
        Fading(IConsumer& consumer, ITimer& timer, const float& factor) : Filter(consumer, timer), _factor(factor) {}
        void stream(Frame& frame) override {
            auto originalPixels = frame.getPixels();
            for (float f = 0; f <= 1; f += _factor) {
                for (size_t i = 0; i < frame.getPixels().size(); ++i) {
                    frame.getPixels()[i] = originalPixels[i];   // reset to original
                    frame.getPixels()[i].applyBrightness(f);    // scale brightness
                }
                _consumer.stream(frame);
                _timer.wait(100);
            }
        }
};