#pragma once
#include "Timing.h"

class Pixel {
    private:
        uint8_t _green;
        uint8_t _red;
        uint8_t _blue;
        Pixel(const uint8_t& green, const uint8_t& red, const uint8_t& blue) : _green(green), _red(red), _blue(blue) {}

    public: 
        static Pixel from(const uint8_t& green, const uint8_t& red, const uint8_t& blue) {
            return Pixel(green, red, blue);
        }

        uint8_t getGreen() const {
            return _green;
        }

        uint8_t getRed() const {
            return _red;
        }

        uint8_t getBlue() const {
            return _blue;
        }
};