#include "ChasingController.h"

ChasingController::ChasingController(ChasingService& service)
    : _service(service)
{}

esp_err_t ChasingController::handle(httpd_req_t *req)
{
    auto* controller = static_cast<ChasingController*>(req->user_ctx);

    if (!controller) {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "No controller context");
        return ESP_FAIL;
    }

    controller->_service.start();

    const char* response = "OK";

    httpd_resp_set_type(req, "text/plain");
    httpd_resp_send(req, response, HTTPD_RESP_USE_STRLEN);

    return ESP_OK;
}