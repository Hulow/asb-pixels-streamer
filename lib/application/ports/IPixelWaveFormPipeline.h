#pragma once
#include "../application/domain/Pixel.h"

class IPixelWaveFormPipeline {
    public: 
        virtual ~IPixelWaveFormPipeline() = default;
        virtual void addPixelToQueue(const Pixel& pixel) = 0;
        virtual void startConsuming() = 0;
};