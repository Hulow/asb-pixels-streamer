#pragma once

#include <cstdint>
#include <array>
#include "driver/rmt_tx.h"

#include "../core/Pixel.h"
#include "TimingBuilder.h"

class Encoder {
    private:
        uint32_t _resolution;
        Timing _timing;
        rmt_encoder_handle_t _encoder = NULL; /* null: I don't point anything yet / stores the callback and also tracks how far along in the data */
        rmt_symbol_word_t _lowSymbol;
        rmt_symbol_word_t _highSymbol;
        rmt_symbol_word_t _resetSymbol;
        uint16_t nsToTick(const uint16_t& timing);
    public:
        Encoder(const uint32_t& resolution, const Timing& timing);
        static size_t encodeColor(
            const void *colors, 
            size_t totalColorsInFrame,
            size_t symbolsCountAlreadySent, 
            size_t availableMemoryBlock,
            rmt_symbol_word_t *symbols,
            bool *done, 
            void *arg
        );

        rmt_encoder_handle_t getEncoder();
};