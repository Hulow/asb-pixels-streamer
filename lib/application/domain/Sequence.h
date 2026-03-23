#pragma once
#include <vector>
#include "Pixel.h"

class Sequence {
    private:
        std::vector<Pixel> _pixels = {};
    public:
        Sequence(const int& pixelsCount) {
            _pixels.reserve(pixelsCount);
        };
        void add(const Pixel& pixel) {
            _pixels.push_back(pixel);
        }
};