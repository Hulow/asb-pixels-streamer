#include "Router.h"

void Router::route(httpd_handle_t server, std::vector<IRoute*> routes) {
       for (auto route : routes) {
            route->registerRoute(server);
        }
}