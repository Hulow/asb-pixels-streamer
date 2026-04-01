#pragma once

#include <vector>

#include "Pixel.h"

class Frame {
    private: 
        std::vector<Pixel> _pixels;
        Frame(const std::vector<Pixel>& pixels) : _pixels(pixels) {}

    public:
        static Frame from(const std::vector<Pixel>& pixels) {
            return Frame(pixels);
        }  

        void add(const Pixel& pixel) {
            _pixels.push_back(pixel);
        }

        std::vector<Pixel>& getPixels() {
            return _pixels;
        }
};