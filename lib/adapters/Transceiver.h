#pragma once

#include "../application/ports/IPixelStreamer.h"
#include "Initializer.h"
#include "Encoder.h"
#include "Transmitter.h"

class Transceiver : public IPixelsStreamer {
    private:
        Initializer _initializer;
        Encoder _encoder;
        Transmitter _transmitter;
    public:
        Transceiver(const rmt_tx_channel_config_t& channelConfigs);
        void stream(const std::vector<Symbol>& symbols);
        void finish();
};