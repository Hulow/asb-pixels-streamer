#pragma once
#include <vector>
#include "../../application/domain/Pixel.h"

class IConsumer {
    public: 
        virtual ~IConsumer() = default;
        virtual void stream(const std::vector<Pixel>& pixel) = 0;
};