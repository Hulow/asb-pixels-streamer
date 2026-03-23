#pragma once

#include "../application/ports/IPixelStreamer.h"
#include "Initializer.h"

class Transceiver : public IPixelsStreamer {
    private:
        Initializer _initializer;
    public:
        Transceiver(const rmt_tx_channel_config_t& channelConfigs);
};