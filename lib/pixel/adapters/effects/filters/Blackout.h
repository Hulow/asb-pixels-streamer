#pragma once

#include <vector>

#include "Filter.h"
#include "../../../application/ports/IConsumer.h"

class Blackout : public Filter {
    public:
        Blackout(IConsumer& consumer) : Filter(consumer) {}
        void stream(const std::vector<Pixel>& pixels) override {}
};