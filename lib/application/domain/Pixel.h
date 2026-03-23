#pragma once
#include "Color.h"
#include "Timing.h"

class Pixel {
    private:
        Color _color;
        Timing _timing;
        Pixel(const Color& color) : _color(color) {}

    public: 
        static Pixel from(const Color& color, const Timing& timing = Timing()) {
            return Pixel(color);
        }

        Timing getTiming() const {
            return _timing;
        }

        std::vector<uint8_t> serializeColor() const {
            return _color.serialize();
        }
};