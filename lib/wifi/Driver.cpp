#include "Driver.h"
#include "esp_wifi.h"
#include "esp_err.h"

/*
    https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/network/esp_wifi.html
*/

void Driver::init() {
    setHardware();
    setResources();
}

void Driver::setHardware() {
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
}

void Driver::setResources() {
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
}

void Driver::setMode(wifi_mode_t mode) {
    ESP_ERROR_CHECK(esp_wifi_set_mode(mode));
}

void Driver::setConfig(wifi_config_t& config) {
    wifi_mode_t mode;
    ESP_ERROR_CHECK(esp_wifi_get_mode(&mode));

    if (mode == WIFI_MODE_AP) {
        ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &config));
    } 
    else if (mode == WIFI_MODE_STA) {
        ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &config));
    } 
    else if (mode == WIFI_MODE_APSTA) {
        ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &config));
    }
}

void Driver::start() {
    ESP_ERROR_CHECK(esp_wifi_start());
}