#pragma once
#include "Color.h"

class Pixel {
    private:
        Color _color;
        Pixel(const Color& color) : _color(color) {}

    public: 
        static Pixel from(const Color& color) {
            return Pixel(color);
        }
};