#pragma once

#include "esp_http_server.h"
#include "../services/ChasingService.h"

class ChasingController {
private:
    ChasingService& _service;

public:
    explicit ChasingController(ChasingService& service);

    static esp_err_t handle(httpd_req_t *req);
};