#pragma once
#include <vector>
#include "driver/rmt_tx.h"
#include <functional>
#include <memory> 

class Transmitter {
    private: 
        rmt_channel_handle_t _channel;
        rmt_encoder_handle_t _encoder;
        rmt_transmit_config_t _streamConfigs;
        rmt_copy_encoder_config_t _encoderConfigs;
        rmt_encoder_handle_t _streamEncoder;

    public: 
        Transmitter(rmt_channel_handle_t channel);
        void transmit(const std::vector<rmt_symbol_word_t>& symbols);
        void finish();
};