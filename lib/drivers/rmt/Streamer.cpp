#include "esp_log.h"

#include "Streamer.h"

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
