#pragma once

#include <cstdint>
#include <array>
#include "driver/rmt_tx.h"

#include "../core/Pixel.h"
#include "TimingBuilder.h"

class Encoder {
    private:
        uint32_t _resolution;
        Timing _timing;
        std::array<rmt_symbol_word_t, 8> toPulses(const uint8_t& color);
        uint16_t mapPulse(const uint16_t& signal);
    public:
        Encoder(const uint32_t& resolution, const Timing& timing);
        std::array<rmt_symbol_word_t, 24> encode(const Pixel& pixel);
        rmt_symbol_word_t encodeResetSignal();
};