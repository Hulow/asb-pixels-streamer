#pragma once

#include "../effects/Filter.h"
#include "../core/IConsumer.h"

class Brightness : public Filter {
    private:
        float _factor;
    
    public:
        Brightness(IConsumer& consumer,const float& factor) : Filter(consumer), _factor(factor) {}
        void enqueuePixel(Pixel& pixel) override {
            pixel.applyBrightness(_factor);  
            return _consumer.enqueuePixel(pixel);
        }
};