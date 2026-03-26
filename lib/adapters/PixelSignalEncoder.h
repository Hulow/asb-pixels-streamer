#pragma once
#include "driver/rmt_tx.h"
#include <array>

#include "../application/domain/Pixel.h"

struct PixelWaveforms {
    static constexpr size_t WAVEFORMS_PER_PIXEL = 24;
    std::array<rmt_symbol_word_t, WAVEFORMS_PER_PIXEL> waveforms;
};

struct PixelTiming {
    uint16_t highTimeSignal;
    uint16_t lowTimeSignal;
    uint16_t highTimeNoSignal;
    uint16_t lowTimeNoSignal;    
};

class PixelSignalEncoder {
    private:
        PixelTiming _timing;
        int _resolution;
        uint16_t toWaveForm(const uint16_t& signal);
    public:
        PixelSignalEncoder(const PixelTiming& timing, const uint32_t& resolution);
        PixelWaveforms toWaveForms(const Pixel& pixel);
};