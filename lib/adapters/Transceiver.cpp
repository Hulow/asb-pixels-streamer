#include "Transceiver.h"
#include "driver/rmt_tx.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/rmt_tx.h"
#include "driver/rmt_encoder.h" // for simple callback encoder

#include "esp_log.h"

Transceiver::Transceiver(const rmt_tx_channel_config_t& channelConfigs) :
    _initializer(channelConfigs), 
    _encoder(channelConfigs.resolution_hz),
    _transmitter(_initializer.getChannel())
{}

void Transceiver::stream(const std::vector<Symbol>& symbols) {
    static const char* TAG = "Transceiver";
    size_t pushed_count = 0;
    for (auto& sym : (_encoder.toRmtSymbols(symbols))) {
        while (!_buffer.push(sym)) {
            vTaskDelay(1 / portTICK_PERIOD_MS);  // yield CPU
        }
        pushed_count++;
    }
    ESP_LOGI(TAG, "Pushed %u symbols to buffer", (unsigned)pushed_count);
}

RingBuffer<4096>& Transceiver::getBuffer() {
    return _buffer;
}

rmt_channel_handle_t Transceiver::getChannelHandle() {
    return _transmitter.getChannel();
}

void Transceiver::test() {
    return _transmitter.start(_buffer);
    
}