#pragma once
#include <cstdint>
#include <array>
#include "driver/rmt_tx.h"
#include "PixelSignalEncoder.h"


struct ResetWaveform {
    static constexpr size_t SYMBOLS = 50; // depends on reset timing
    std::array<rmt_symbol_word_t, SYMBOLS> symbols;
};


class ResetSignalGenerator {
private:
    uint16_t resetDuration; // in ticks

public:
    explicit ResetSignalGenerator(uint16_t duration)
        : resetDuration(duration) {}

    PixelWaveforms generate() const {
        PixelWaveforms wf;

        for (size_t i = 0; i < PixelWaveforms::WAVEFORMS_PER_PIXEL; i++) {
            wf.waveforms[i].duration0 = resetDuration;
            wf.waveforms[i].level0 = 0;
            wf.waveforms[i].duration1 = 0;
            wf.waveforms[i].level1 = 0;
        }

        return wf;
    }
};