#pragma once

#include <cstdint>
class ITimer {
    public:
        virtual void wait(uint32_t ms) = 0;
};