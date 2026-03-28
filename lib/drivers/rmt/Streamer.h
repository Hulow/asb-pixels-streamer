#pragma once 

#include <array>
#include "driver/rmt_tx.h"

#include "Queue.h"

class Streamer {
    private:
        Queue _queue;

    public: 
        void pushToQueue(const std::array<rmt_symbol_word_t, 24>& symbols);
        void printQueue();
};