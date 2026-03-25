#include "Transmitter.h"
#include <functional>
#include "freertos/FreeRTOS.h"
#include <driver/rmt_tx.h>
#include "esp_log.h"

Transmitter::Transmitter(rmt_channel_handle_t channel) : _channel(channel) {
    _encoderConfigs = {};
    _streamEncoder = nullptr;
    _streamConfigs = {};
    _streamConfigs.loop_count = 0;
    // rmt_new_copy_encoder(&_encoderConfigs, &_streamEncoder);
}

//Define your callback
size_t rmt_simple_encoder_callback(
    const void* src,
    size_t src_size,
    size_t src_offset,
    size_t wanted_num,
    rmt_symbol_word_t* dest,
    bool* completed,
    void* user_data)
{
     auto* buffer = static_cast<RingBuffer<4096>*>(user_data);
    size_t written = 0;
    rmt_symbol_word_t item;

        // printf("Callback entered: wanted_num=%zu\n", wanted_num); // <<<<< ADD THIS

    // static const char* TAG = "Transmitter - callback";
    // ESP_LOGI(TAG, "calling callback");

    while (written < wanted_num && buffer->pop(item)) {
        dest[written++] = item;
    }

    *completed = buffer->empty(); // true if no more symbols left
        // printf("Callback: wrote %d symbols, buffer empty=%d\n", (int)written, *completed);

    return written;  
}


void Transmitter::start(RingBuffer<4096>& buffer) {
    static const char* TAG = "Transmitter - start";
    ESP_LOGI(TAG, "before transmit");
    ESP_LOGI(TAG, "Channel handle: %p", _channel);
    ESP_LOGI(TAG, "Encoder: %p", _streamEncoder);
    ESP_LOGI(TAG, "Buffer address: %p", &buffer);
    // printf("START transmit with buffer size");
    rmt_simple_encoder_config_t cfg = {};
    cfg.callback = rmt_simple_encoder_callback;  // callback defined in your file
    cfg.arg = &buffer;                            // pass your transceiver’s ring buffer
    cfg.min_chunk_size = 8;                       // safe default

    // Create the simple encoder
    esp_err_t err = rmt_new_simple_encoder(&cfg, &_streamEncoder);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to create encoder: %d", err);
        return;
    }

    ESP_LOGI(TAG, "rmt_new_simple_encoder returned: %d, encoder: %p", err, _streamEncoder);

    rmt_enable(_channel);

    rmt_transmit_config_t tx_config = {};
    tx_config.loop_count = 0;      // no loop
    tx_config.flags = RMT_TX_FLAGS_DEFAULT;   
    
    rmt_transmit(_channel, _streamEncoder, nullptr, 0, &tx_config);
    // default flags

}

rmt_channel_handle_t Transmitter::getChannel() {
    return _channel;
}

// RingBuffer<4096> Transmitter::getBuffer() {

// }