#pragma once

#include <vector>

#include "Filter.h"
#include "../../../core/IConsumer.h"

class Brightness : public Filter {
    private:
        float _factor;
    
    public:
        Brightness(IConsumer& consumer,const float& factor) : Filter(consumer), _factor(factor) {}
        void stream(const std::vector<Pixel>& pixels) override {}
};