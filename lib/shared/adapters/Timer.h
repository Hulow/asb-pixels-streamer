#pragma once

#include <cstdint>
#include "../ports/ITime.h"

class Timer : public ITime {
    public:
        void wait(const uint32_t& ms) override;
};