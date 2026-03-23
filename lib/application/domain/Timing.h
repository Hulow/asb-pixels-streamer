#pragma once
#include <cstdint>

class Timing {
    private:
        uint16_t _highTimeLineNoSignal  = 300;
        uint16_t _lowTimeLineNoSignal = 1090;
        uint16_t _highTimeLineSignal = 1090;
        uint16_t _lowTimeLineSignal = 320;
        uint16_t _lowResetDuration = 30000;
    
    public: 
        Timing(
            uint16_t highNoSignal = 300,
            uint16_t lowNoSignal = 1090,
            uint16_t highSignal = 1090,
            uint16_t lowSignal = 320,
            uint16_t lowReset = 30000
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