#pragma once
#include <cstdint>
#include <array>
#include "driver/rmt_tx.h"
#include "PixelSignalEncoder.h"
#include <cmath>

struct SingleResetWaveform {
    uint16_t duration0;
    uint8_t level0;
    uint16_t duration1;
    uint8_t level1;
};

class ResetSignalGenerator {

public:
    ResetSignalGenerator() {}

    // Generate just one reset waveform
    rmt_symbol_word_t generate() const {
        rmt_symbol_word_t wf;
        wf.duration0 = 5000; // long low signal
        wf.level0    = 0;
        wf.duration1 = 0;           // unused
        wf.level1    = 0;           // unused
        return wf;
    }
};

// class ResetSignalGenerator {
// private:
//     uint16_t resetDuration; // in ticks

// public:
//     ResetSignalGenerator(uint16_t duration)
//         : resetDuration(duration) {}

//     PixelWaveforms generate() const {
//         PixelWaveforms wf;

//          for (size_t i = 0; i < PixelWaveforms::WAVEFORMS_PER_PIXEL; i++) {
//             wf.waveforms[i].duration0 = 300;
//             wf.waveforms[i].level0 = 0;
//             wf.waveforms[i].duration1 = 0;
//             wf.waveforms[i].level1 = 0;
//         }

//         return wf;
//     }

//     uint16_t toWaveForm(const uint16_t& signal) const {
//     double ticks = static_cast<double>(signal) * 10000000 / 1e9;
//     return static_cast<uint16_t>(std::round(ticks));
//     }
// };

