#include "Transmitter.h"

Transmitter::Transmitter(const rmt_tx_channel_config_t& configs, const Timing& timing) : 
    _channel(configs),
    _encoder(configs.resolution_hz, timing),
    _streamer(
        _channel.getChannel(), 
        _encoder.getEncoder()
    )
{}

void Transmitter::stream(Frame& frame) {
    _streamer.stream(
        frame.getPixels()
    );
}
