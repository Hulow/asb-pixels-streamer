#pragma once
#include "PixelFilter.h"

class Brightness : public PixelFilter {
    private:
        float _factor;
    
    public:
        Brightness(IPixelConsumer& consumer,const float& factor) : PixelFilter(consumer), _factor(factor) {}
        void enqueuePixel(const Pixel& pixel) override {
            return _consumer.enqueuePixel(
                Pixel::from(
                    (pixel.getGreen() * _factor),
                    (pixel.getRed() * _factor),
                    (pixel.getBlue() * _factor)
                )
            );
        }
};