#include "Transmitter.h"
#include "esp_log.h"

Transmitter::Transmitter(const rmt_tx_channel_config_t& configs, const Timing& timing) : 
    _channel(configs),
    _encoder(configs.resolution_hz, timing),
    _streamer()
{}

void Transmitter::encode(const Pixel& pixel) {
    _streamer.pushToQueue(
        _encoder.encode(pixel)
    );
}

void Transmitter::printQueue() {
    _streamer.printQueue();
}