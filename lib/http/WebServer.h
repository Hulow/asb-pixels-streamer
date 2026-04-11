#pragma once

#include "esp_http_server.h"

class WebServer {
public:
    void start();

private:
    httpd_handle_t server = nullptr;
};