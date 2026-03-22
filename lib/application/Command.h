#pragma once
#include <cstdint>

class Command {
    private:
        uint8_t _pixel;
        Command(const uint8_t& pixel) : _pixel(pixel) {};
    
    public:
        static Command from(const uint8_t& pixel) {
            return Command(pixel);
        }

        uint8_t getPixel() const {
            return _pixel;
        }
};