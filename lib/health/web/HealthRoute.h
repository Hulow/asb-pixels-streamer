#pragma once

#include "esp_http_server.h"
#include "HealthController.h"
#include "../../http/IRoute.h"

class HealthRoute : public IRoute {
private:
    HealthController& _controller;

public:
    explicit HealthRoute(HealthController& controller);
    void registerRoute(httpd_handle_t server) override;
};