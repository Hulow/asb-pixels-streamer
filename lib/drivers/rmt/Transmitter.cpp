#include "Transmitter.h"
#include "esp_log.h"

Transmitter::Transmitter(const rmt_tx_channel_config_t& configs, const Timing& timing) : 
    _channel(configs),
    _encoder(configs.resolution_hz, timing) 
{}

void Transmitter::encode(const Pixel& pixel) {
    auto pulses = _encoder.encode(pixel);
        for (int i=0; i<24; i++) {
            printf("Pulse %2d: high=%d low=%d\n", i, pulses[i].duration1, pulses[i].duration0);
        }
}