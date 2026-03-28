#pragma once
#include "driver/rmt_tx.h"
#include "WaveFormsQueue.h"
#include "PixelSignalEncoder.h"
#include "ResetSignalGenerator.h"


struct EncoderState {
    PixelWaveforms current;
    size_t index = 0;
    bool hasCurrent = false;
};

class WaveFormStreamer {
    private:
        rmt_encoder_handle_t _streamEncoder;
        rmt_channel_handle_t _channel;
        WaveFormsQueue<5000> _queue;
        esp_err_t dummyStransmit();
    public:
    WaveFormStreamer(const rmt_channel_handle_t& channel);
    void stream();
    void addWaveformsToQueue(const PixelWaveforms& waveForms);
    void addResetWaveform(const rmt_symbol_word_t& waveForm);
};