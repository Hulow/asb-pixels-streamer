#include "WiFiManager.h"

WiFiManager::WiFiManager() {
    initNVS();
    setNetwork();
    setEventMessagingSystem();
    setRessources();
    setStorage();
    configureNetwork();
    setOperatingMode();
    buildOperatingConfigs();
    setOperatingConfigs();
    start();
}

void WiFiManager::initNVS() {
    ESP_ERROR_CHECK(nvs_flash_init());
}

void WiFiManager::setNetwork() {
    ESP_ERROR_CHECK(esp_netif_init());
}

void WiFiManager::configureNetwork() {
    /* set:
        - DHCP server
        - IP assignment
        - gateway
        - Network completion
    */
    esp_netif_create_default_wifi_ap();
}

void WiFiManager::setEventMessagingSystem() {
    ESP_ERROR_CHECK(esp_event_loop_create_default());
}

void WiFiManager::setStorage() {
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
}

void WiFiManager::setRessources() {
    wifi_init_config_t configs = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&configs));
}

void WiFiManager::setOperatingMode() {
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
}

void WiFiManager::buildOperatingConfigs() {
    strcpy((char*)_operatingConfigs.ap.ssid, "ESP32_VIQ");
    strcpy((char*)_operatingConfigs.ap.password, "12345678");
    
    _operatingConfigs.ap.authmode = WIFI_AUTH_WPA2_PSK;
    _operatingConfigs.ap.max_connection = 4;
    _operatingConfigs.ap.channel = 6;
}

void WiFiManager::setOperatingConfigs() {
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &_operatingConfigs));
}

void WiFiManager::start() {
    ESP_ERROR_CHECK(esp_wifi_start());
}