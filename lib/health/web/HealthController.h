#pragma once

#include "../service/HealthService.h"
#include "esp_http_server.h"

class HealthController {
    private: 
        HealthService& _service;
public:
    explicit HealthController(HealthService& service);
    static esp_err_t handle(httpd_req_t *req);
};