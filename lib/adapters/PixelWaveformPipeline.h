#pragma once

#include "ChannelWaveForm.h"
#include "ChannelConfigsBuilder.h"
#include "PixelSignalEncoder.h"
#include "WaveFormStreamer.h"
#include "../application/ports/IPixelConsumer.h"

class PixelWaveFormPipeline : public IPixelConsumer {
    private:
        ChannelWaveForm _channel;
        PixelSignalEncoder _encoder;
        WaveFormStreamer _streamer;
    public:
        explicit PixelWaveFormPipeline(
                const ChannelConfigsBuilder& configsBuilder, 
                const PixelTiming& timing
        );
        static PixelWaveFormPipeline createWS2815(const ChannelConfigsBuilder& configsBuilder);
        void enqueuePixel(const Pixel& pixel);
        void signalLastPixel();
        void start();
};


