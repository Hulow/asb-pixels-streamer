#pragma once 

#include <array>
#include "driver/rmt_tx.h"

#include "Queue.h"

class Streamer {
    private:
        rmt_encoder_handle_t _streamEncoder;
        rmt_channel_handle_t _channel;
        Queue _queue;
        esp_err_t transit();

    public: 
        Streamer(const rmt_channel_handle_t& channel);
        void pushPixelToQueue(const std::array<rmt_symbol_word_t, 24>& symbols);
        void pushResetSignalToQueue(const rmt_symbol_word_t& symbol);
        void printQueue();
        void stream();
};