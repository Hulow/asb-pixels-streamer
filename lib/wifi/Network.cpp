#include "Network.h"
#include "esp_err.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_wifi.h"

void Network::init() {
    setNetworkStack();
    setEventLoop();
    setHotSpot();
}

/* 
    https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/network/esp_netif.html 
        - Provides an abstraction layer for the application on top of the TCP/IP stack
        - Handles things like IP addresses, DNS
*/

void Network::setNetworkStack() {
    ESP_ERROR_CHECK(esp_netif_init());
}

/* 
    Event Loop Library from System API
    https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/system/esp_event.html
        - The event loop is the bridge between events and event handlers
        - The event source publishes events to the event loop using the APIs provided by the event loop library

*/

void Network::setEventLoop() {
    ESP_ERROR_CHECK(esp_event_loop_create_default());
}

void Network::setHotSpot() {
    esp_netif_create_default_wifi_ap();
}