#include "Transmitter.h"
#include <iostream>
#include <functional>

Transmitter::Transmitter(rmt_channel_handle_t channel) : _channel(channel) {
    _encoderConfigs = {};
    _streamEncoder = nullptr;
    _streamConfigs = {};
    _streamConfigs.loop_count = 0;
}

void Transmitter::transmit(const std::vector<rmt_symbol_word_t>& symbols) {}