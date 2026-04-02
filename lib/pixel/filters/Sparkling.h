#pragma once

#include <cstdlib>
#include "Filter.h"


class Sparkling : public Filter {
    private:
        int _sparkleCount;
    
    public:
        Sparkling(IConsumer& consumer, int sparkleCount = 3) : Filter(consumer), _sparkleCount(sparkleCount) {}
        void stream(Frame& frame) override {
            auto originalPixels = frame.getPixels();

            resetFrame(frame);
            applySparkles(frame, originalPixels);

            _consumer.stream(frame);
        }

        void resetFrame(Frame& frame) {
            for (auto& pixel : frame.getPixels()) {
                pixel.turnOff();
            }
        }

        void applySparkles(Frame& frame, const std::vector<Pixel>& originalPixels) {
            for (int i = 0; i < _sparkleCount; ++i) {
                size_t idx = std::rand() % frame.getPixels().size();
                frame.getPixels()[idx] = originalPixels[idx];
            }
        }
};