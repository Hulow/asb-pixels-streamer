#include "ChasingRoute.h"

ChasingRoute::ChasingRoute(ChasingController& controller) : _controller(controller) {}

void ChasingRoute::registerRoute(httpd_handle_t server)
{
    httpd_uri_t uri = {
        .uri = "/pixel/chasing",
        .method = HTTP_GET,
        .handler = ChasingController::handle,
        .user_ctx = &_controller
    };

    httpd_register_uri_handler(server, &uri);
}