#include "Initializer.h"

Initializer::Initializer(const rmt_tx_channel_config_t& channelConfigs) : _channelConfigs(channelConfigs) {
    setupConfigs();
    turnOnTransmitter();
}

void Initializer::setupConfigs() {
    rmt_new_tx_channel(&_channelConfigs, &_channel);
}

void Initializer::turnOnTransmitter() {
    rmt_enable(_channel);
}