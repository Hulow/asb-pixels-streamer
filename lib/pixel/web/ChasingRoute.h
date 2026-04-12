#pragma once

#include "esp_http_server.h"
#include "ChasingController.h"
#include "../../http/IRoute.h"

class ChasingRoute : public IRoute {
public:
    void registerRoute(httpd_handle_t server) override {
        httpd_uri_t uri = {
            .uri = "/chasing",
            .method = HTTP_GET,
            .handler = ChasingController::handle,
            .user_ctx = nullptr
        };
        
        httpd_register_uri_handler(server, &uri);
    }
};