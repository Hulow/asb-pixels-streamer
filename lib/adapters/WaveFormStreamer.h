#pragma once
#include "driver/rmt_tx.h"
#include "WaveFormsQueue.h"
#include "PixelSignalEncoder.h"

struct EncoderState {
    PixelWaveforms current;
    size_t index = 0;
    bool hasCurrent = false;
};

class WaveFormStreamer {
    private:
        rmt_encoder_handle_t _streamEncoder;
        rmt_channel_handle_t _channel;
        WaveFormsQueue<1500> _queue;
        esp_err_t dummyStransmit();
    public:
    WaveFormStreamer(const rmt_channel_handle_t& channel);
    void stream();
    void addWaveformsToQueue(const PixelWaveforms& waveForms);
};