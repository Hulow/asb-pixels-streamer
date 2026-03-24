#include "Transmitter.h"
#include <iostream>
#include <functional>
#include "freertos/FreeRTOS.h"

Transmitter::Transmitter(rmt_channel_handle_t channel) : _channel(channel) {
    _encoderConfigs = {};
    _streamEncoder = nullptr;
    _streamConfigs = {};
    _streamConfigs.loop_count = 0;
}

void Transmitter::transmit(const std::vector<rmt_symbol_word_t>& symbols) {
    rmt_new_copy_encoder(&_encoderConfigs, &_streamEncoder);
    esp_err_t err = rmt_transmit(
        _channel,
        _streamEncoder,
        symbols.data(),
        symbols.size() * sizeof(rmt_symbol_word_t),
        &_streamConfigs
    );

    if (err != ESP_OK) {
        printf("rmt_transmit failed: %d\n", err);
    }

    _streamEncoder = nullptr;

    rmt_tx_wait_all_done(_channel, portMAX_DELAY);
    rmt_del_encoder(_streamEncoder);
}