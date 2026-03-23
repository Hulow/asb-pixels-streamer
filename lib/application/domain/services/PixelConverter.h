#pragma once
#include "../Pixel.h"
#include "../Symbol.h"

class PixelConverter {
    private: 
        std::vector<Symbol> _symbols;
        Pixel _pixel;
        Symbol toSymbol(const uint8_t& bit);
        PixelConverter(const Pixel& pixel);
    public:
        static PixelConverter fromPixel(const Pixel& pixel);
        std::vector<Symbol> toSymbols();
};