#include "PixelWaveformPipeline.h"
#include "PixelSignalEncoder.h"

PixelWaveFormPipeline::PixelWaveFormPipeline(const ChannelConfigsBuilder& configs, const PixelTiming& timing) : _channel(configs),  _encoder(timing, configs.build().resolution_hz), _streamer(_channel.getChannel()) {}

PixelWaveFormPipeline PixelWaveFormPipeline::createWS2815(const ChannelConfigsBuilder& configs) {
    static constexpr PixelTiming ws2815Timing{
        .highTimeSignal   = 300,
        .lowTimeSignal    = 1090,
        .highTimeNoSignal = 1090,
        .lowTimeNoSignal  = 320
    };

    return PixelWaveFormPipeline(configs, ws2815Timing);
}

void PixelWaveFormPipeline::addPixelToQueue(const Pixel& pixel) {
    _streamer.addWaveformsToQueue(
        _encoder.toWaveForms(pixel)
    );
}