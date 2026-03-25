#include "rmt.h"
#include <cmath>
#include "esp_log.h"

Rmt::Rmt(const rmt_tx_channel_config_t& channelConfigs) : _channelConfigs(channelConfigs) {
    _encoderConfigs = {};
    _streamEncoder = nullptr;
    _streamConfigs = {};
    _streamConfigs.loop_count = 0;
    // Create and enable TX channel once
    static const char* TAG = "RMT - constructor";
    esp_err_t err = rmt_new_tx_channel(&_channelConfigs, &_channel);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to create RMT TX channel: %d", err);
        _channel = nullptr;
        return;
    }

    err = rmt_enable(_channel);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to enable RMT TX channel: %d", err);
        _channel = nullptr;
        return;
    }

    ESP_LOGI(TAG, "RMT TX channel initialized on GPIO %d", _channelConfigs.gpio_num);
}

std::vector<rmt_symbol_word_t> Rmt::toRmtSymbols(const std::vector<Symbol>& symbols) {
    std::vector<rmt_symbol_word_t> rmtSymbols;
    for (const auto& symbol : symbols) {
        rmtSymbols.push_back(toRmtSymbol(symbol));
    }

    return rmtSymbols;
}

rmt_symbol_word_t Rmt::toRmtSymbol(const Symbol& symbol) {
    return rmt_symbol_word_t({
        .duration0 = toRmtTick(symbol.getHighDuration()),
        .level0 = 1,
        .duration1 = toRmtTick(symbol.getLowDuration()),
        .level1 = 0
   });
}

/* unsafe */
uint16_t Rmt::toRmtTick(const uint16_t& timing) {
    double ticks = static_cast<double>(timing) * _channelConfigs.resolution_hz / 1e9;
    return static_cast<uint16_t>(std::round(ticks));
}

//Define your callback
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
    auto* queue = static_cast<SymbolsQueue<1500>*>(user_data);
    size_t written = 0;
    rmt_symbol_word_t item;

    while (written < wanted_num && queue->pop(item)) {
        dest[written++] = item;
    }

    *completed = queue->empty();
    
    return written;  
}


void Rmt::stream() {
    static const char* TAG = "RMT - stream";

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
    esp_err_t err3 = rmt_new_simple_encoder(&cfg, &_streamEncoder);
    if (err3 != ESP_OK) {
        ESP_LOGE(TAG, "Failed to create encoder: %d", err3);
        return;
    }

    ESP_LOGI(TAG, "rmt_new_simple_encoder returned: %d, encoder: %p", err3, _streamEncoder);


    rmt_transmit_config_t tx_config = {};
    tx_config.loop_count = 0;

    while (!_queue.empty()) {
        uint8_t dummy = 0;
        esp_err_t err4 = rmt_transmit(
            _channel, //channel that created by rmt_new_tx_channel()
            _streamEncoder, //RMT encoder that created by various factory APIs like rmt_new_bytes_encoder() /rmt_encoder_handle_t
            &dummy, //payload -- [in] The raw data to be encoded into RMT symbols
            1,   //payload_bytes -- [in] Size of the payload in bytes 
            &tx_config//config -- [in] Transmission specific configuration
        );

        if (err4 != ESP_OK) {
            ESP_LOGI(TAG, "Transmit failed: %d", err4);
        }
    }

    //If encoder != nullptr, payload must be nullptr and payload_bytes must be 0. ✅ You did that, correct.
}

void Rmt::addSymbolsToQueue(const std::vector<rmt_symbol_word_t>& symbols) {
    _queue.pushSymbols(symbols);
}