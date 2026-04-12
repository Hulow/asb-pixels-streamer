#pragma once

#include "esp_http_server.h"
#include <vector>
#include "IRoute.h"

/*
    https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/protocols/esp_http_server.html
*/

class WebServer {
public:
    WebServer(const std::vector<IRoute*>& routes);
    bool start();
    void registerRoutes();

private:
    httpd_handle_t _server = nullptr;
    httpd_config_t _configs;
    const std::vector<IRoute*>& _routes;
};