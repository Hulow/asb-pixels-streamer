#pragma once
#include <cstdint>

class Symbol {

    private:
        uint16_t _lowDuration;
        uint16_t _highDuration; 
        Symbol(
            const uint16_t& lowDuration, 
            const uint16_t& highDuration
        ) :
            _lowDuration(lowDuration), 
            _highDuration(highDuration) 
        {}

    public:
        static Symbol from(
            const uint16_t& lowDuration, 
            const uint16_t& highDuration
        ) {
            return Symbol(lowDuration, highDuration);
        }

        uint16_t getLowDuration() const {
            return _lowDuration;
        }

        uint16_t getHighDuration() const {
            return _highDuration;
        }
};