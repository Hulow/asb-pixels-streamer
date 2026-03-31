#include "Transmitter.h"
#include "esp_log.h"

Transmitter::Transmitter(const rmt_tx_channel_config_t& configs, const Timing& timing) : 
    _channel(configs),
    _encoder(configs.resolution_hz, timing),
    _streamer(
        _channel.getChannel(), 
        _encoder.getEncoder()
    )
{}

void Transmitter::pushPixel(Pixel& pixel) {}

void Transmitter::pushResetSignal() {}

void Transmitter::printQueue() {}

void Transmitter::start() {}
