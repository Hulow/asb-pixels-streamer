#pragma once

#include "driver/rmt_tx.h"

class SymbolBuilder {
    private:
        rmt_symbol_word_t _pulse;
    public:
        SymbolBuilder() {
            _pulse = {};
        }

        SymbolBuilder& clear() {
            _pulse = {};
            return *this;
        }

        SymbolBuilder& lowDuration(const uint16_t& signal) {
            _pulse.duration0 = signal;
            return *this;
        }

        SymbolBuilder& lowLevel(const int& level) {
            _pulse.level0 = level;
            return *this;
        }

        SymbolBuilder& highLevel(const int& level) {
            _pulse.level1 = level;
            return *this;
        }

        SymbolBuilder& highDuration(const uint16_t& signal) {
            _pulse.duration1 = signal;
            return *this;
        }

        rmt_symbol_word_t build() {
            return _pulse;
        }
};