#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "Streamer.h"
#include <string>

Streamer::Streamer(
    const rmt_channel_handle_t& channel, 
    const rmt_encoder_handle_t& encoder) 
    : 
        _channel(channel), 
        _encoder(encoder) 
    {
    _transmitConfig = {
        .loop_count = 0
    };
}

std::vector<uint8_t> flattenPixels(const std::vector<Pixel>& pixels) {
    std::vector<uint8_t> buffer;
    buffer.reserve(pixels.size() * 3); // 3 bytes per pixel

    for (const auto& p : pixels) {
        buffer.push_back(p.getGreen());
        buffer.push_back(p.getRed());
        buffer.push_back(p.getBlue());
    }

    return buffer;
}

void Streamer::stream(const std::vector<Pixel> pixels) {

    auto bytes = flattenPixels(pixels);

    std::string line;
    for (size_t i = 0; i < bytes.size(); ++i) {
        char buf[4];
        snprintf(buf, sizeof(buf), "%02X ", bytes[i]);
        line += buf;

        // Print 16 bytes per line
        if ((i + 1) % 16 == 0 || i == bytes.size() - 1) {
            ESP_LOGI("TAG", "%s", line.c_str());
            line.clear();
        }
    }

    ESP_ERROR_CHECK(
        rmt_transmit(
            _channel, 
            _encoder, 
            bytes.data(), 
            bytes.size(), 
            &_transmitConfig
        )
    );   

    ESP_ERROR_CHECK(rmt_tx_wait_all_done(_channel, portMAX_DELAY));
}
