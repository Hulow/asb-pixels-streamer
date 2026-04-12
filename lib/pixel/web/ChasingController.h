#pragma once

#include "esp_http_server.h"


class ChasingController {
    public:
        static esp_err_t handle(httpd_req_t *req);
};