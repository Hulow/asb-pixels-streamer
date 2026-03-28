#pragma once

#include "driver/rmt_tx.h"

class PulseBuilder {
    private:
        rmt_symbol_word_t _pulse;
    public:
        PulseBuilder() {
            _pulse = {};
        }

        PulseBuilder& clear() {
            _pulse = {};
            return *this;
        }

        PulseBuilder& lowDuration(const uint16_t& signal) {
            _pulse.duration0 = signal;
            return *this;
        }

        PulseBuilder& lowLevel(const int& level) {
            _pulse.level0 = level;
            return *this;
        }

        PulseBuilder& highLevel(const int& level) {
            _pulse.level1 = level;
            return *this;
        }

        PulseBuilder& highDuration(const uint16_t& signal) {
            _pulse.duration1 = signal;
            return *this;
        }

        rmt_symbol_word_t build() {
            return _pulse;
        }
};