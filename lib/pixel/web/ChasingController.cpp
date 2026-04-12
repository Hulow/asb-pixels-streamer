#include "ChasingController.h"

esp_err_t ChasingController::handle(httpd_req_t *req) {
    const char *response = "OK";

    httpd_resp_set_type(req, "text/plain");
    httpd_resp_send(req, response, strlen(response));

    return ESP_OK;
}