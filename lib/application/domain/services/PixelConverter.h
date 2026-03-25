#pragma once
#include "../Pixel.h"
#include "../Symbol.h"

class PixelConverter {
    private: 
        std::vector<Symbol> _symbols;
        Pixel _pixel;
        Timing _timing;
        Symbol toSymbol(const uint8_t& bit);
        PixelConverter(const Pixel& pixel, const Timing& timing);
    public:
        static PixelConverter from(const Pixel& pixel, const Timing& timing);
        std::vector<Symbol> toSymbols();
        void addResetTiming();
};