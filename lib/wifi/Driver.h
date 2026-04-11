#pragma once

#include "esp_wifi.h"

class Driver {
    private:
        void setHardware();
        void setResources();
    public:
        void init();
        void start();
        void setMode(wifi_mode_t mode);
        void setConfig(wifi_config_t& config);
};