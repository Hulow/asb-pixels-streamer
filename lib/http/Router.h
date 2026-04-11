#pragma once

#include "esp_http_server.h"

class Router {
public:
    static void route(httpd_handle_t server);
};