#pragma once
#include <cstdint>

class Command {
    private:
        uint8_t _green;
        uint8_t _red;
        uint8_t _blue;
        int _pixelsCount;
        Command(
            const uint8_t& green, 
            const uint8_t& red, 
            const uint8_t&blue, 
            const int& pixelsCount
        ) : 
            _green(green), 
            _red(red), 
            _blue(blue),
            _pixelsCount(pixelsCount)
        {};
    
    public:
        static Command from(
            const uint8_t& green, 
            const uint8_t& red, 
            const uint8_t& blue, 
            const int& pixelsCount
        ) {
            return Command(green, red, blue, pixelsCount);
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

        int getPixelsCount() const {
            return _pixelsCount;
        }
};