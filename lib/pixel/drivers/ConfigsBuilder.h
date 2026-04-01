#pragma once

#include "driver/rmt_tx.h"

class ConfigsBuilder {
private:
    rmt_tx_channel_config_t _config;

public:
    ConfigsBuilder() { 
        _config = {}; 
    }

    ConfigsBuilder& gpioNum(gpio_num_t gpio_num) {
        _config.gpio_num = gpio_num;
        return *this;
    }

    ConfigsBuilder& clock(rmt_clock_source_t clock) { 
        _config.clk_src = clock;
        return *this;
    }
    
    ConfigsBuilder& memBlockSymbols(int blocks) { 
        _config.mem_block_symbols = blocks;
        return *this;
    }

    ConfigsBuilder& queueDepth(int depth) {
        _config.trans_queue_depth = depth;
        return *this;
    }

    ConfigsBuilder& resolutionHz(int hz) {
        _config.resolution_hz = hz;
        return *this;
    }

    rmt_tx_channel_config_t build() const {
        return _config;
    }
};