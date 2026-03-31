#pragma once

#include <cstdint>

struct Timing {
    float highTimeSignal;
    float lowTimeSignal;
    float highTimeNoSignal;
    float lowTimeNoSignal;
    float resetTime;
};

class TimingBuilder {
    private:
        Timing _timing;
    public:
        TimingBuilder() {
            _timing = {};
        }

        TimingBuilder& highTimeSignal(int highTimeSignal) {
            _timing.highTimeSignal = highTimeSignal;
            return *this;
        }

        TimingBuilder& lowTimeSignal(int lowTimeSignal) {
            _timing.lowTimeSignal = lowTimeSignal;
            return *this;
        }

        TimingBuilder& highTimeNoSignal(int highTimeNoSignal) {
            _timing.highTimeNoSignal = highTimeNoSignal;
            return *this;
        }

        TimingBuilder& lowTimeNoSignal(int lowTimeNoSignal) {
            _timing.lowTimeNoSignal = lowTimeNoSignal;
            return *this;
        }

        TimingBuilder& resetTime(int resetTime) {
            _timing.resetTime = resetTime;
            return *this;
        }

        Timing build() {
            return _timing;
        }
};