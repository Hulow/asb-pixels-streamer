#pragma once 

#include <array>
#include <vector>
#include "driver/rmt_tx.h"

#include "../../core/Pixel.h"

class Streamer {
    private:
        rmt_channel_handle_t _channel;
        rmt_encoder_handle_t _encoder;
        rmt_transmit_config_t _transmitConfig;

    public: 
        Streamer(const rmt_channel_handle_t& channel, const rmt_encoder_handle_t& encoder);
        void stream(const std::vector<Pixel> pixels);
};