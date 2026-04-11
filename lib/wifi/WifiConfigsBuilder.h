#pragma once

#include <string>
#include "esp_wifi.h"
#include <cstring>

class WifiConfigsBuilder {
    private:
        wifi_config_t _configs;
    public:

        WifiConfigsBuilder() {
            _configs = {};
        }

        WifiConfigsBuilder withSsid(const char * ssid) {
           strcpy((char*)_configs.ap.ssid, ssid);

           return *this;
        }

        WifiConfigsBuilder withPassword(const char * password) {
            strcpy((char*)_configs.ap.password, password);

            return *this;
        }

        WifiConfigsBuilder withAuthMode(wifi_auth_mode_t mode) {
            _configs.ap.authmode = mode;

            return *this;
        }

        WifiConfigsBuilder withMaxConnection(const int number) {
            _configs.ap.max_connection = number;

            return *this;
        }

        WifiConfigsBuilder withChannelNumber(const int number) {
            _configs.ap.channel = number;

            return *this;
        }

        wifi_config_t build() {
            return _configs;
        }
};