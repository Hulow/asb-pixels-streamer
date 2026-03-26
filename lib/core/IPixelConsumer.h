#pragma once
#include "../core/Pixel.h"

class IPixelConsumer {
    public: 
        virtual ~IPixelConsumer() = default;
        virtual void enqueuePixel(const Pixel& pixel) = 0;
        virtual void start() = 0;
        virtual void signalLastPixel() = 0;
};