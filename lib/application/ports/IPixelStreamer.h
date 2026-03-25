#pragma once

#include <functional>
#include "../domain/Symbol.h"
#include <driver/rmt_tx.h>


class IPixelsStreamer {
    public:
        virtual ~IPixelsStreamer() = default;
        virtual std::vector<rmt_symbol_word_t> toRmtSymbols(const std::vector<Symbol>& symbols) = 0;
        virtual void stream() = 0;
        virtual void addSymbolsToQueue(const std::vector<rmt_symbol_word_t>& symbols) = 0;
};
