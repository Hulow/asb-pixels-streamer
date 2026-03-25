#pragma once
#include <vector>
#include <functional>
#include <memory> 
#include "RingBuffer.h"
#include "driver/rmt_tx.h"
#include "RingBuffer.h"

class Transmitter {
    private: 
        rmt_channel_handle_t _channel;
        rmt_encoder_handle_t _encoder;
        rmt_transmit_config_t _streamConfigs;
        rmt_copy_encoder_config_t _encoderConfigs;
        rmt_encoder_handle_t _streamEncoder;
        RingBuffer<4096> _buffer;

    public: 
        Transmitter(rmt_channel_handle_t channel);
        void start(RingBuffer<4096>& buffer);
        rmt_channel_handle_t getChannel();
        // RingBuffer<4096> getBuffer();
};