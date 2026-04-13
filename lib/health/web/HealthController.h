#pragma once

#include "esp_http_server.h"

class HealthController {
public:
    explicit HealthController();
    static esp_err_t handle(httpd_req_t *req);
};