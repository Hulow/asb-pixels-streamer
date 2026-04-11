#pragma once

#include "esp_wifi.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include <cstring>

class WiFiManager {
    public:
        WiFiManager();

    private:
        wifi_config_t _operatingConfigs = {};
        void initNVS();
        void setNetwork();
        void configureNetwork();
        void setEventMessagingSystem();
        void setStorage();
        void setRessources();
        void setOperatingMode();
        void buildOperatingConfigs();
        void setOperatingConfigs();
        void start();
};