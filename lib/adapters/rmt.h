#pragma once
#include "driver/rmt_tx.h"
#include "../application/domain/Symbol.h"
#include "SymbolsQueue.h"
#include "../application/ports/IPixelStreamer.h"

class Rmt : public IPixelsStreamer {
    private:
        rmt_tx_channel_config_t _channelConfigs;
        rmt_channel_handle_t _channel;
        rmt_encoder_handle_t _encoder;
        rmt_transmit_config_t _streamConfigs;
        rmt_copy_encoder_config_t _encoderConfigs;
        rmt_encoder_handle_t _streamEncoder;
        SymbolsQueue<1500> _queue;
        uint16_t toRmtTick(const uint16_t& timing);
        rmt_symbol_word_t toRmtSymbol(const Symbol& symbols);

    public:
        Rmt(const rmt_tx_channel_config_t& channelConfigs);
        std::vector<rmt_symbol_word_t> toRmtSymbols(const std::vector<Symbol>& symbols);
        void stream();
        void addSymbolsToQueue(const std::vector<rmt_symbol_word_t>& symbols);
};