#include "WifiManager.h"
#include "WifiConfigsBuilder.h"

WifiManager::WifiManager() {
    init();
}

void WifiManager::init() {
    nvs.init();
    network.init();
    driver.init();
    driver.setMode(WIFI_MODE_AP);
    auto configs = WifiConfigsBuilder()
        .withSsid("ESP32_VIQ")
        .withPassword("12345678")
        .withAuthMode(WIFI_AUTH_WPA2_PSK)
        .withMaxConnection(4)
        .withChannelNumber(6)
        .build();
    driver.setConfig(configs);
}

void WifiManager::start() {
     driver.start();
}