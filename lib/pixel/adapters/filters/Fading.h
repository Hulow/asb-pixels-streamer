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
            fadeOut(frame, originalPixels);
        }

        void fadeIn(Frame& frame, const std::vector<Pixel>& originalPixels) {
            for (float factor = 0; factor <= 1.0f; factor += _factor) {
                applyBrightness(frame, originalPixels, factor);
                _consumer.stream(frame);
                _timer.wait(100);
            }
        }

        void fadeOut(Frame& frame, const std::vector<Pixel>& originalPixels) {
            for (float factor = 1.0f; factor >= 0.0f; factor -= _factor) {
                applyBrightness(frame, originalPixels, factor);
                _consumer.stream(frame);
                _timer.wait(100);
            }
        }

        void applyBrightness(Frame& frame, const std::vector<Pixel>& originalPixels, float factor) {
            for (size_t i = 0; i < frame.getPixels().size(); ++i) {
                frame.getPixels()[i] = originalPixels[i]; 
                frame.getPixels()[i].applyBrightness(factor);
            }
        }
};