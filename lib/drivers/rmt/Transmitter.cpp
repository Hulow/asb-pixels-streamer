#include "Transmitter.h"
#include "esp_log.h"

Transmitter::Transmitter(const rmt_tx_channel_config_t& configs, const Timing& timing) : 
    _channel(configs),
    _encoder(configs.resolution_hz, timing),
    _streamer(_channel.getChannel())
{}

void Transmitter::pushPixel(const Pixel& pixel) {
    _streamer.pushPixelToQueue(
        _encoder.encode(pixel)
    );
}

void Transmitter::pushResetSignal() {
    _streamer.pushResetSignalToQueue(
        _encoder.encodeResetSignal()
    );
}

void Transmitter::printQueue() {
    _streamer.printQueue();
}

void Transmitter::start() {
    _streamer.stream();
}
