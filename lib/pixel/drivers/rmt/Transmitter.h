#pragma once

#include "Channel.h"
#include "../ConfigsBuilder.h"
#include "Encoder.h"
#include "Streamer.h"
#include "../../domain/IConsumer.h"
#include "../../domain/Pixel.h"
#include "../../domain/Frame.h"

class Transmitter : public IConsumer {
    private:
        Channel _channel;
        Encoder _encoder;
        Streamer _streamer;
    public:
        Transmitter(const rmt_tx_channel_config_t& configs, const Timing& timing);
        void stream(Frame& frame);
};


