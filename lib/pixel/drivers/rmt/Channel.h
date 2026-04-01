#pragma once
#include "driver/rmt_tx.h"

#include "../ConfigsBuilder.h"

class Channel {
    private:
        rmt_tx_channel_config_t _configs;
        rmt_channel_handle_t _channel;
    public:
        explicit Channel(const rmt_tx_channel_config_t& configs);
        rmt_channel_handle_t getChannel() const;
};