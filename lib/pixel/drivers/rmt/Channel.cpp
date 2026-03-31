#include "Channel.h"
#include "esp_log.h"

Channel::Channel(const rmt_tx_channel_config_t& configs) : _configs(configs) {
    static const char* TAG = "Channel";

    ESP_LOGI(TAG, "Create RMT TX channel");
    ESP_ERROR_CHECK(rmt_new_tx_channel(&_configs, &_channel));

    ESP_LOGI(TAG, "Enable RMT TX channel");
    ESP_ERROR_CHECK(rmt_enable(_channel));

}

rmt_channel_handle_t Channel::getChannel() const {
    return _channel;
}