#include "Router.h"
#include "../pixel/controllers/ChasingController.h"

void Router::route(httpd_handle_t server) {
    httpd_uri_t status_uri = {
        .uri = "/chasing",
        .method = HTTP_GET,
        .handler = ChasingController::handle,
        .user_ctx = nullptr
    };

    httpd_register_uri_handler(server, &status_uri);
}