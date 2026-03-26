#include "esp_log.h"
#include "WaveFormStreamer.h"

WaveFormStreamer::WaveFormStreamer(const rmt_channel_handle_t& channel) : _channel(channel) {}

void WaveFormStreamer::addWaveformsToQueue(const PixelWaveforms& waveForms) {
    for (const rmt_symbol_word_t  wm : waveForms.waveforms) {
         _queue.push(wm);
    }
}

size_t encoderCallback(
    const void* src,
    size_t src_size,
    size_t src_offset,
    size_t wanted_num,
    rmt_symbol_word_t* dest,
    bool* completed,
    void* user_data
)
{
    auto* queue = static_cast<WaveFormsQueue<1500>*>(user_data);
    size_t written = 0;
    rmt_symbol_word_t item;

    while (written < wanted_num && queue->pop(item)) {
        dest[written++] = item;
    }

    *completed = queue->empty();
    
    return written;  
}

void WaveFormStreamer::stream() {
    static const char* TAG = "WaveFormStreamer";

    if (_queue.empty()) {
        ESP_LOGW(TAG, "Queue empty, nothing to transmit");
        return;
    }

    if (_streamEncoder) {
        rmt_del_encoder(_streamEncoder);
        _streamEncoder = nullptr;
    }

    rmt_simple_encoder_config_t cfg = {};
    cfg.callback = encoderCallback; 
    cfg.arg = &_queue;                           
    cfg.min_chunk_size = 1;

    // Create the simple encoder
    if (esp_err_t err = rmt_new_simple_encoder(&cfg, &_streamEncoder) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to create encoder: %d", err);
        return;
    }

    while (!_queue.empty()) {
           if (esp_err_t err = dummyStransmit() != ESP_OK) {
                ESP_LOGI(TAG, "Transmit failed: %d", err);
           }
    }
}

esp_err_t WaveFormStreamer::dummyStransmit() {
    rmt_transmit_config_t tx_config = {};
    tx_config.loop_count = 0;

    return rmt_transmit(
        _channel,
        _streamEncoder, 
        0,
        1, 
        &tx_config
    );
}