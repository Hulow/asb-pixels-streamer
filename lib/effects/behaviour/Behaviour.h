#pragma once

#include <vector>

#include "../core/IConsumer.h"

struct State {
    int currentPixel;
    int pixelsCount;
    int chasingLength ;
};

class Behaviour : public IConsumer {
    protected:
        IConsumer& _consumer; 
    public: 
        Behaviour(IConsumer& consumer) : _consumer(consumer) {}
        
        virtual ~Behaviour() = default;

        virtual void stream(const std::vector<Pixel>& pixel) = 0;
};