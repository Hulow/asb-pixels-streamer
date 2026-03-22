#include "Logger.h"
#include "esp_log.h"

void Logger::info(const std::string& tag, const std::string& msg) {
    esp_log_level_set(tag.c_str(), ESP_LOG_DEBUG);
    ESP_LOGI(tag.c_str(), "%s", msg.c_str());
}