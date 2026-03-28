#include <cmath>
#include <array>

#include "Encoder.h"
#include "PulseBuilder.h"

Encoder::Encoder(const uint32_t& resolution, const Timing& timing) : _resolution(resolution), _timing(timing) {}

std::array<rmt_symbol_word_t, 24> Encoder::encode(const Pixel& pixel) {
    auto g = toPulses(pixel.getGreen());
    auto r = toPulses(pixel.getRed());
    auto b = toPulses(pixel.getBlue());

    std::array<rmt_symbol_word_t, 24> pulses{
        g[0], g[1], g[2], g[3], g[4], g[5], g[6], g[7],
        r[0], r[1], r[2], r[3], r[4], r[5], r[6], r[7],
        b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]
    };

    return pulses;
}

rmt_symbol_word_t Encoder::encodeResetSignal() {
    PulseBuilder pulse = PulseBuilder();
    return pulse
        .lowLevel(0)
        .lowDuration(_timing.resetTime)
        .highLevel(0)
        .highDuration(1)
        .build();
}

std::array<rmt_symbol_word_t, 8> Encoder::toPulses(const uint8_t& color) {
    PulseBuilder pulse = PulseBuilder();
    std::array<rmt_symbol_word_t, 8> pulses{};

    size_t idx = 0;
    
    for (int bit = 7; bit >=0; bit --) {
        pulse.clear();
        uint8_t value = (color >> bit) & 0x01;
        if (value) {
            pulse
                .highDuration(mapPulse(_timing.highTimeSignal))
                .highLevel(1)
                .lowDuration(mapPulse(_timing.lowTimeSignal))
                .lowLevel(0);
        } else {
            pulse
                .highDuration(mapPulse(_timing.highTimeNoSignal))
                .highLevel(1)
                .lowDuration(mapPulse(_timing.lowTimeNoSignal))
                .lowLevel(0);

        }

        pulses[idx++] = pulse.build();
    }

    return pulses;
}

uint16_t Encoder::mapPulse(const uint16_t& signal) {
    double ticks = static_cast<double>(signal) * _resolution / 1e9;
    return static_cast<uint16_t>(std::round(ticks));
}
