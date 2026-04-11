#pragma once

#include "esp_http_server.h"

class WebConfigBuilder {
    private:
        httpd_config_t _configs;
public:
    WebConfigBuilder() {
        _configs = HTTPD_DEFAULT_CONFIG();
    }
    static httpd_config_t createDefault() {
        httpd_config_t config = HTTPD_DEFAULT_CONFIG();

        return config;
    }

    WebConfigBuilder withLruPurgeEnable(const bool enabled) {
        _configs.lru_purge_enable = enabled;

        return *this;
    }

    WebConfigBuilder withTimeOut(const int ms) {
        _configs.recv_wait_timeout = ms;

        return *this;
    }

    httpd_config_t build() {
        
        return _configs;
    }
};