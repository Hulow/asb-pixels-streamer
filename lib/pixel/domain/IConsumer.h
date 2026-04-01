#pragma once

#include "Pixel.h"
#include "Frame.h"

class IConsumer {
    public: 
        virtual ~IConsumer() = default;
        virtual void stream(Frame& frame) = 0;
};