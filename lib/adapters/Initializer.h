#pragma once

#include "driver/rmt_tx.h"

class Initializer {
    private:
        rmt_tx_channel_config_t _channelConfigs;
        rmt_channel_handle_t _channel;
        void setupConfigs();
        void turnOnTransmitter();
    public:
        Initializer(const rmt_tx_channel_config_t& channelConfigs);
};