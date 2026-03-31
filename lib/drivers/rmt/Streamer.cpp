#include "esp_log.h"

#include "Streamer.h"

Streamer::Streamer(const rmt_channel_handle_t& channel, const rmt_encoder_handle_t& encoder) : _channel(channel), _encoder(encoder) {
    _transmitConfig = {
        .loop_count = 0
    };
}

void Streamer::pushPixelToQueue(const std::array<rmt_symbol_word_t, 24>& symbols) {
}

void Streamer::pushResetSignalToQueue(const rmt_symbol_word_t& symbol) {
}

void Streamer::printQueue() {
}

void Streamer::stream(const std::vector<Pixel> pixels) {

    ESP_ERROR_CHECK(
        rmt_transmit(
            _channel, 
            _encoder, 
            &pixels, 
            sizeof(pixels), 
            &_transmitConfig
        )
    );   
}
