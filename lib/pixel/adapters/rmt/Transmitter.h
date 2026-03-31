#pragma once

#include <vector>

#include "Channel.h"
#include "ConfigsBuilder.h"
#include "Encoder.h"
#include "Streamer.h"
#include "../../core/Pixel.h"
#include "../../application/ports/IConsumer.h"

class Transmitter : public IConsumer {
    private:
        Channel _channel;
        Encoder _encoder;
        Streamer _streamer;
    public:
        Transmitter(const rmt_tx_channel_config_t& configs, const Timing& timing);
        void stream(const std::vector<Pixel>& pixels);
};


