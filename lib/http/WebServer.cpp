#include "WebServer.h"
#include "WebConfigBuilder.h"
#include "Router.h"
#include <string.h>

WebServer::WebServer(const std::vector<IRoute*>& routes) : _routes(routes) {
    _server = nullptr;
};

bool WebServer::start() {

 auto config = WebConfigBuilder()
        .withLruPurgeEnable(true)
        .withTimeOut(10)
        .build();

    return httpd_start(&_server, &config) == ESP_OK;
}

void WebServer::registerRoutes() {
    Router::route(_server, _routes);
}