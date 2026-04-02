#pragma once

#include <vector>

#include "Pixel.h"

class Frame {
    private: 
        std::vector<Pixel> _pixels;

    public:
        Frame() {}

        void add(const Pixel& pixel) {
            _pixels.push_back(pixel);
        }

        std::vector<Pixel>& getPixels() {
            return _pixels;
        }
};