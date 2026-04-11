#include "WebServer.h"
#include "WebConfigBuilder.h"
#include "Router.h"
#include <string.h>
#include "esp_log.h"

void WebServer::start() {
    ESP_LOGI("HTTP", "Starting HTTP server...");

    auto config = WebConfigBuilder()
        .withLruPurgeEnable(true)
        .withTimeOut(10)
        .build();

    if (httpd_start(&server, &config) == ESP_OK && server) {
        Router::route(server);
        ESP_LOGI("HTTP", "Routes registered");
    } else {
        ESP_LOGE("HTTP", "Failed to start HTTP server");
    }
}