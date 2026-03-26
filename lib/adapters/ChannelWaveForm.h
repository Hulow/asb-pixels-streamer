#pragma once
#include "driver/rmt_tx.h"

#include "ChannelConfigsBuilder.h"

class ChannelWaveForm {
    private:
        rmt_tx_channel_config_t _configs;
        rmt_channel_handle_t _channel;
    public:
        explicit ChannelWaveForm(const ChannelConfigsBuilder& configs);
        rmt_channel_handle_t getChannel() const;
};