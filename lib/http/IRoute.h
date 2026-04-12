#pragma once

#include "esp_http_server.h"

class IRoute {
    public:
        virtual ~IRoute() = default;
        virtual void registerRoute(httpd_handle_t server) = 0;
};