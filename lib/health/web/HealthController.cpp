#include "HealthController.h"

HealthController::HealthController(HealthService& service) : _service(service) {}

esp_err_t HealthController::handle(httpd_req_t *req)
{
    auto* controller = static_cast<HealthController*>(req->user_ctx);

    if (!controller) {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "No health controller context");
        return ESP_FAIL;
    }


    ChipInfo chip = controller->_service.monitor();

    static char json[256];

    HealthMapper::toJson(json, sizeof(json), chip);

    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, json, HTTPD_RESP_USE_STRLEN);

    return ESP_OK;
}