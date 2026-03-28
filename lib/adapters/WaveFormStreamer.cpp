#include "esp_log.h"
#include "WaveFormStreamer.h"

WaveFormStreamer::WaveFormStreamer(const rmt_channel_handle_t& channel) : _channel(channel) {
    _streamEncoder = nullptr;
}

void WaveFormStreamer::addWaveformsToQueue(const PixelWaveforms& waveForms) {
    for (const rmt_symbol_word_t  wm : waveForms.waveforms) {
        // ESP_LOGI("QUEUE", "Symbol duration0: %d, level0: %d, duration 1: %d, level 1: %d", wm.duration0, wm.level0, wm.duration1, wm.level1);
        bool success = _queue.push(wm);
        if (!success) {
            ESP_LOGI("QUEUE", "Queue full! Pixel symbols dropped!");
        }
    }
}

void WaveFormStreamer::addResetWaveform(const rmt_symbol_word_t& wm) {
      bool success = _queue.push(wm);
    //   ESP_LOGI("QUEUE", "RESET SYMBOL duration0: %d, level0: %d, duration 1: %d, level 1: %d", wm.duration0, wm.level0, wm.duration1, wm.level1);
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
    auto* queue = static_cast<WaveFormsQueue<5000>*>(user_data);
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

    //cleaning up the previous RMT encoder
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
    uint8_t dummy = 0;

    return rmt_transmit(
        _channel,
        _streamEncoder, 
        &dummy,
        1, 
        &tx_config
    );
}