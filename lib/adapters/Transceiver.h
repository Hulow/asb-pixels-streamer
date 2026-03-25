#pragma once

#include "../application/ports/IPixelStreamer.h"
#include "Initializer.h"
#include "Encoder.h"
#include "Transmitter.h"
#include "RingBuffer.h"
#include "driver/rmt_tx.h"

class Transceiver : public IPixelsStreamer {
    private:
        Initializer _initializer;
        Encoder _encoder;
        Transmitter _transmitter;
        RingBuffer<4096> _buffer;
    public:
        Transceiver(const rmt_tx_channel_config_t& channelConfigs);
        void stream(const std::vector<Symbol>& symbols);
        RingBuffer<4096>& getBuffer();
        rmt_channel_handle_t getChannelHandle();
        void test();
};