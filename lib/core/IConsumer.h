#pragma once
#include <vector>
#include "../core/Pixel.h"

class IConsumer {
    public: 
        virtual ~IConsumer() = default;
        virtual void stream(const std::vector<Pixel>& pixel) = 0;
};