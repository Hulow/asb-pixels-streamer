#include "HealthRoute.h"

HealthRoute::HealthRoute(HealthController& controller) : _controller(controller) {}

void HealthRoute::registerRoute(httpd_handle_t server)
{
    httpd_uri_t uri = {
        .uri = "/health",
        .method = HTTP_GET,
        .handler = HealthController::handle,
        .user_ctx = &_controller
    };

    httpd_register_uri_handler(server, &uri);
}