#pragma once

#include "esp_http_server.h"
#include <vector>
#include "IRoute.h"

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