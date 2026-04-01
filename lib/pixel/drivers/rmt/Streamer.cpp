#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "Streamer.h"

Streamer::Streamer(
    const rmt_channel_handle_t& channel, 
    const rmt_encoder_handle_t& encoder) 
    : 
        _channel(channel), 
        _encoder(encoder) 
    {
    _transmitConfig = {
        .loop_count = 0,
        .flags = {
            .eot_level = 1,
            .queue_nonblocking = 1
        }
    };
}

void Streamer::stream(const std::vector<Pixel> pixels) {

    std::vector<uint8_t> buffer;
    buffer.reserve(
        pixels.size() * 3
    );

    for (const auto& pixel : pixels) {
        auto bytes = pixel.toBytes();
        buffer.insert(
            buffer.end(), 
            bytes.begin(), 
            bytes.end()
        );
    }

    ESP_ERROR_CHECK(
        rmt_transmit(
            _channel, 
            _encoder, 
            buffer.data(), 
            buffer.size(), 
            &_transmitConfig
        )
    );   

    ESP_ERROR_CHECK(
        rmt_tx_wait_all_done(
            _channel, 
            portMAX_DELAY
        )
    );
}
