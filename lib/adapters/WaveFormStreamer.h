#pragma once
#include "driver/rmt_tx.h"
#include "WaveFormsQueue.h"

class WaveFormStreamer {
    private:
        rmt_encoder_handle_t _streamEncoder;
        rmt_channel_handle_t _channel;
        WaveFormsQueue<1500> _queue;
    public:
    WaveFormStreamer(const rmt_channel_handle_t& channel);
     void stream();
};