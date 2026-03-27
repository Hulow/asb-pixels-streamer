#include <cstdint>
#include "ITimer.h"

class Timer : public ITimer {
    public:
        void wait(const uint32_t& ms);
};