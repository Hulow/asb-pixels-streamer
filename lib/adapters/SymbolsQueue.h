#pragma once
#include <cstddef>
#include <vector>
#include "driver/rmt_tx.h"

template <size_t SIZE>
class SymbolsQueue {
private:
    rmt_symbol_word_t buffer[SIZE];
    size_t head = 0;
    size_t tail = 0;

public:
    bool push(const rmt_symbol_word_t& item) {
        size_t next = (head + 1) % SIZE;

        if (next == tail) {
            return false; // buffer full
        }

        buffer[head] = item;
        head = next;
        return true;
    }

    bool pushSymbols(const std::vector<rmt_symbol_word_t>& items) {
        for (const auto& item : items) {
            if (!push(item)) {
                return false; // stop if buffer becomes full
            }
        }
        return true;
    }

    bool pop(rmt_symbol_word_t& item) {
        if (head == tail) {
            return false; // buffer empty
        }

        item = buffer[tail];
        tail = (tail + 1) % SIZE;
        return true;
    }

    bool empty() const {
        return head == tail;
    }
};