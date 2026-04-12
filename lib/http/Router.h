#pragma once

#include "esp_http_server.h"
#include <vector>

#include "IRoute.h"

class Router {
public:
    static void route(httpd_handle_t server, std::vector<IRoute*> routes);
};