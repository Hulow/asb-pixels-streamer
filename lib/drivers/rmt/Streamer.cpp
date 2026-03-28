#include "Streamer.h"

void Streamer::pushPixelToQueue(const std::array<rmt_symbol_word_t, 24>& symbols) {
    _queue.pushSymbols(symbols);
}

void Streamer::pushResetSignalToQueue(const rmt_symbol_word_t& symbol) {
    _queue.push(symbol);
}

void Streamer::printQueue() {
    _queue.printQueue();
}