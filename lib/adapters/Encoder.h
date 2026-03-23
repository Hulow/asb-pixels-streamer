#pragma once
#include <vector>
#include "driver/rmt_tx.h"

#include "../application/domain/Symbol.h"

class Encoder {
    private: 
        int _resolution;
        uint16_t toRmtTick(const uint16_t& timing);
        rmt_symbol_word_t toRmtSymbol(const Symbol& symbol);
    public:
        Encoder(const int& resolution);
        std::vector<rmt_symbol_word_t> toRmtSymbols(const std::vector<Symbol>& symbols);
};