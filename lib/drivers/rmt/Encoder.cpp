#include <cmath>
#include <array>
#include "esp_log.h"

#include "Encoder.h"
#include "SymbolBuilder.h"

Encoder::Encoder(const uint32_t& resolution, const Timing& timing) : _resolution(resolution), _timing(timing) {

    static const char* TAG = "Encoder";
    ESP_LOGI(TAG, "Create simple callback-based encoder");

    const rmt_simple_encoder_config_t encoderCfg = {
        .callback = Encoder::encodeColor,
        .arg = this,
        .min_chunk_size = 64
    };

    ESP_ERROR_CHECK(rmt_new_simple_encoder(&encoderCfg, &_encoder));

    _lowSymbol = {
        .duration0 = static_cast<uint16_t>(_timing.lowTimeNoSignal * _resolution / 1000000),
        .level0 = 1,
        .duration1 = static_cast<uint16_t>(_timing.lowTimeNoSignal * _resolution / 1000000),
        .level1 = 0,
    };

    _highSymbol = {
        .duration0 = static_cast<uint16_t>(_timing.highTimeSignal * _resolution / 1000000),
        .level0 = 1,
        .duration1 = static_cast<uint16_t>(_timing.lowTimeNoSignal * _resolution / 1000000),
        .level1 = 0,
    };

    _resetSymbol = {
        .duration0 = static_cast<uint16_t>(_resolution / 1000000 * _timing.resetTime / 2),
        .level0 = 0,
        .duration1 = static_cast<uint16_t>(_resolution / 1000000 * _timing.resetTime / 2),
        .level1 = 0,
    };
}

size_t Encoder::encodeColor(
    const void *colors, 
    size_t totalColorsInFrame,
    size_t symbolsCountAlreadySent, 
    size_t availableMemoryBlock,
    rmt_symbol_word_t *symbols, 
    bool *done, 
    void *arg
) {

    Encoder* self = static_cast<Encoder*>(arg);

    if(availableMemoryBlock < 8) {
        return 0;
    }

    size_t indexOfNextColorToEncode = symbolsCountAlreadySent / 8;

    uint8_t *colorsInBytes = (uint8_t*)colors;

    if (indexOfNextColorToEncode < totalColorsInFrame) {
        size_t symbolPos = 0;
        for (int bitmask = 0x80; bitmask != 0; bitmask >>= 1) {
            if (colorsInBytes[indexOfNextColorToEncode]&bitmask) {
                symbols[symbolPos++] = self->_highSymbol;
            } else {
                symbols[symbolPos++] = self->_lowSymbol;
            }
        }

        return symbolPos;
    } else {
        symbols[0] = self->_resetSymbol;
        *done = 1;
        return 1;
    }
}