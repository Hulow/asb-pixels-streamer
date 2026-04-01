#pragma once

#include "Filter.h"
#include "../../../application/ports/IConsumer.h"
#include "../../../application/domain/Frame.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class Brightness : public Filter {
    private:
        float _factor;
    
    public:
        Brightness(IConsumer& consumer,const float& factor, ITimer& timer) : Filter(consumer, timer), _factor(factor) {}
        void stream(Frame& frame) override {
            for (auto& pixel : frame.getPixels()) {
                pixel.applyBrightness(_factor);
            }

            _consumer.stream(frame);
            _timer.wait(100);
        }
};