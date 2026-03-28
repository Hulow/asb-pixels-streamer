#pragma once
#include "../core/Pixel.h"

class IConsumer {
    public: 
        virtual ~IConsumer() = default;
        virtual void pushPixel(const Pixel& pixel) = 0;
        virtual void start() = 0;
        virtual void pushResetSignal() = 0;
};