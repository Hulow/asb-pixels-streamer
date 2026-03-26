#include "PixelSignalEncoder.h"
#include <cmath>

PixelSignalEncoder::PixelSignalEncoder(const PixelTiming& timing, const uint32_t& resolution) : _timing(timing), _resolution(resolution) {}

PixelWaveforms PixelSignalEncoder::toWaveForms(const Pixel& pixel) {
    PixelWaveforms wf;

    size_t idx = 0;

    auto encode = [&](uint8_t byte) {
        for (int bit = 7; bit >= 0; --bit) {

            uint8_t value = (byte >> bit) & 0x01;

            rmt_symbol_word_t sym0;

            if (value) {
                sym0.duration0 = toWaveForm(_timing.highTimeSignal);
                sym0.level0    = 1;
                sym0.duration1 = toWaveForm(_timing.lowTimeSignal);
                sym0.level1    = 0;
            } else {
                sym0.duration0 = toWaveForm(_timing.highTimeNoSignal);
                sym0.level0    = 1;
                sym0.duration1 = toWaveForm(_timing.lowTimeNoSignal);
                sym0.level1    = 0;
            }

            wf.waveforms[idx++] = sym0;
        }
    };

    encode(pixel.getGreen());
    encode(pixel.getRed());
    encode(pixel.getBlue());

     return wf;
}

uint16_t PixelSignalEncoder::toWaveForm(const uint16_t& signal) {
    double ticks = static_cast<double>(signal) * _resolution / 1e9;
    return static_cast<uint16_t>(std::round(ticks));
}