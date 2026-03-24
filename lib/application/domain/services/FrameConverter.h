#pragma once
#include "../Pixel.h"
#include "../Symbol.h"
#include "../Frame.h"
#include "../Timing.h"

class FrameConverter {
    private: 
        Frame _frame;
        Timing _timing;
        std::vector<Symbol> _symbols;
        void toSymbol(
            const Pixel& pixel
        );
        Symbol mapSymbol(
            const uint8_t& bit
        );
        void reset();
        FrameConverter(
            const Frame& frame, 
            const Timing& timing = Timing(300, 1090, 1090, 320, 30000)
        );
    public:
        static FrameConverter from(const Frame& frame);
        std::vector<Symbol> toSymbols();
};