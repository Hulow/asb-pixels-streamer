#include "Channel.h"
#include "esp_log.h"

Channel::Channel(const rmt_tx_channel_config_t& configs) : _configs(configs) {
    static const char* TAG = "ChannelWaveForm";
    if (esp_err_t errChannel = rmt_new_tx_channel(&_configs, &_channel) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to create RMT TX channel: %d", errChannel);
        _channel = nullptr;
        return;
    }

    if (esp_err_t errEnableChannel = rmt_enable(_channel) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to enable RMT TX channel: %d", errEnableChannel);
        _channel = nullptr;
        return;
    }
}

rmt_channel_handle_t Channel::getChannel() const {
    return _channel;
}