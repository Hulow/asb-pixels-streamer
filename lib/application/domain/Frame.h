#pragma once
#include <vector>
#include "Pixel.h"

class Frame {
    private:
        std::vector<Pixel> _pixels;
        Frame(const std::vector<Pixel>& pixels) : _pixels(pixels) {};
    
    public: 
        static Frame from(const std::vector<Pixel>& pixels) {
            return Frame(pixels);
        }

        const std::vector<Pixel>& getPixels() const {
            return _pixels;
        }
};