#pragma once

#include "esp_http_server.h"
#include "ChasingController.h"
#include "../../http/IRoute.h"

class ChasingRoute : public IRoute {
private:
    ChasingController& _controller;

public:
    explicit ChasingRoute(ChasingController& controller);
    void registerRoute(httpd_handle_t server) override;
};