#pragma once

#include "Frame.h"

class IConsumer {
    public: 
        virtual ~IConsumer() = default;
        virtual void stream(Frame& frame) = 0;
};