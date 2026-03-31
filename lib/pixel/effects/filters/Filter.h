#pragma once

#include <vector>

#include "../../core/IConsumer.h"

class Filter : public IConsumer {
    protected:
        IConsumer& _consumer;

    public:
        Filter(IConsumer& consumer) : _consumer(consumer) {}

        virtual ~Filter() = default;

        virtual void stream(const std::vector<Pixel>& pixels) override = 0;

};