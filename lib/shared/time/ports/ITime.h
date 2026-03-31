#pragma once

class ITime {
    public: 
        virtual ~ITime() = default;
        virtual void wait(const uint32_t& ms) = 0;
};