#pragma once

#include "../application/ports/IPixelStreamer.h"
#include "Initializer.h"
#include "Encoder.h"

class Transceiver : public IPixelsStreamer {
    private:
        Initializer _initializer;
        Encoder _encoder;
    public:
        Transceiver(const rmt_tx_channel_config_t& channelConfigs);
};