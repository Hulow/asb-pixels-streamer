#pragma once

#include "driver/rmt_tx.h"

class ChannelConfigsBuilder {
private:
    rmt_tx_channel_config_t _config;

public:
    ChannelConfigsBuilder() { 
        _config = {}; 
    }

    ChannelConfigsBuilder& gpioNum(gpio_num_t gpio_num) {
        _config.gpio_num = gpio_num;
        return *this;
    }

    ChannelConfigsBuilder& clock(rmt_clock_source_t clock) { 
        _config.clk_src = clock;
        return *this;
    }

    ChannelConfigsBuilder& memBlockSymbols(int blocks) { 
        _config.mem_block_symbols = blocks;
        return *this;
    }

    ChannelConfigsBuilder& queueDepth(int depth) {
        _config.trans_queue_depth = depth;
        return *this;
    }

    ChannelConfigsBuilder& resolutionHz(int hz) {
        _config.resolution_hz = hz;
        return *this;
    }

    rmt_tx_channel_config_t build() const {
        return _config;
    }
};