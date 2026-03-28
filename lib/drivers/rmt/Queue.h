#pragma once

#include <array>
#include "driver/rmt_tx.h"
#include "esp_log.h"

class Queue {
    private:
        rmt_symbol_word_t* _symbols;
        size_t _front = 0;
        size_t _back = 0;
         size_t _capacity;

    public:

        Queue(size_t capacity = 600) : _capacity(capacity) {
            _symbols = new rmt_symbol_word_t[_capacity];
        }

        void pushSymbols(std::array<rmt_symbol_word_t, 24> symbols) {
            for (const auto& symbol : symbols) {
                push(symbol);
            }
        }
        
        void push(const rmt_symbol_word_t& symbol) {
            _symbols[_back] = symbol;
            _back = (_back + 1) % 600;
        }

        bool pop(rmt_symbol_word_t& symbol) {
            if (_front == _back) {
                ESP_LOGI("QUEUE", "EMPTY");
                return false; // buffer empty
            }

            symbol = _symbols[_front];
            _front = (_front + 1) % 600;
            return true;
        }

        bool empty() const {
            return _front == _back;
        }

        void printQueue() const {
            for (size_t i = 0; i < _back; i++) {
                ESP_LOGI("QUEUE", "symbol %d - high %d - low %d",
                        i, _symbols[i].duration0, _symbols[i].duration1);
            }
    }
};