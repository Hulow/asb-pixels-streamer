#include "Transceiver.h"

Transceiver::Transceiver(const rmt_tx_channel_config_t& channelConfigs) :
    _initializer(channelConfigs), 
    _encoder(channelConfigs.resolution_hz),
    _transmitter(_initializer.getChannel())
{}


void Transceiver::stream(const std::vector<Symbol>& symbols) {
    _transmitter.transmit(_encoder.toRmtSymbols(symbols));
}
