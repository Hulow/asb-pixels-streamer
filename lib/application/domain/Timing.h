#pragma once
#include <cstdint>

class Timing {
    private:
        uint16_t _highTimeLineNoSignal;
        uint16_t _lowTimeLineNoSignal;
        uint16_t _highTimeLineSignal;
        uint16_t _lowTimeLineSignal;
        uint16_t _lowResetDuration;
    
    public: 
        Timing(
            uint16_t highNoSignal,
            uint16_t lowNoSignal,
            uint16_t highSignal,
            uint16_t lowSignal,
            uint16_t lowReset
        ) 
        : _highTimeLineNoSignal(highNoSignal),
          _lowTimeLineNoSignal(lowNoSignal),
          _highTimeLineSignal(highSignal),
          _lowTimeLineSignal(lowSignal),
          _lowResetDuration(lowReset)
        {}

        uint16_t getHighTimeLineNoSignal() const { return _highTimeLineNoSignal; }
        uint16_t getLowTimeLineNoSignal()  const { return _lowTimeLineNoSignal; }
        uint16_t getHighTimeLineSignal()   const { return _highTimeLineSignal; }
        uint16_t getLowTimeLineSignal()    const { return _lowTimeLineSignal; }
        uint16_t getLowResetDuration()     const { return _lowResetDuration; }
};