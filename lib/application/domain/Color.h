#pragma once
#include <cstdint>

class Color {
    private:
        uint8_t _green;
        uint8_t _red;
        uint8_t _blue;
        Color(const uint8_t& green, const uint8_t& red, const uint8_t& blue) : _green(green), _red(red), _blue(blue) {}
    
    public: 
        static Color from(const uint8_t& green, const uint8_t& red, const uint8_t& blue) {
            return Color(green, red, blue);
        }
};