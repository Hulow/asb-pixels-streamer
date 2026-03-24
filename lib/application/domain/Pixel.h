#pragma once
#include "Color.h"
#include "Timing.h"

class Pixel {
    private:
        Color _color;
        Pixel(const Color& color) : _color(color) {}

    public: 
        static Pixel from(const Color& color) {
            return Pixel(color);
        }

        std::vector<uint8_t> serializeColor() const {
            return _color.serialize();
        }
};