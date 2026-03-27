#pragma once

#include <cstdint>
class ITimer {
    public:
        virtual void wait(const uint32_t& ms) = 0;
};