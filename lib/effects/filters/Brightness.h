#pragma once

#include "Filter.h"
#include "../../core/IConsumer.h"

class Brightness : public Filter {
    private:
        float _factor;
    
    public:
        Brightness(IConsumer& consumer,const float& factor) : Filter(consumer), _factor(factor) {}
        void pushPixel(Pixel& pixel) override {
            pixel.applyBrightness(_factor);  
            return _consumer.pushPixel(pixel);
        }
};