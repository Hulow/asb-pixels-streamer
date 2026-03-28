#include "Streamer.h"

void Streamer::pushToQueue(const std::array<rmt_symbol_word_t, 24>& symbols) {
    _queue.pushSymbols(symbols);
}

void Streamer::printQueue() {
    _queue.printQueue();
}