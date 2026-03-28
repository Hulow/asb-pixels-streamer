#pragma once 

#include <array>
#include "driver/rmt_tx.h"

#include "Queue.h"

class Streamer {
    private:
        Queue _queue;

    public: 
        void pushPixelToQueue(const std::array<rmt_symbol_word_t, 24>& symbols);
        void pushResetSignalToQueue(const rmt_symbol_word_t& symbol);
        void printQueue();
};