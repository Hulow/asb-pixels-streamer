#pragma once
#include <vector>
#include "../../application/domain/Pixel.h"
#include "../../application/domain/Frame.h"

class IConsumer {
    public: 
        virtual ~IConsumer() = default;
        virtual void stream(Frame& frame) = 0;
};