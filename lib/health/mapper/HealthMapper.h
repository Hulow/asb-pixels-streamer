#pragma once

#include <cstddef>
#include <inttypes.h>

#include "../service/HealthService.h"


class HealthMapper {
    public:
        static void toJson(
            char* buffer, 
            size_t size, 
            const HealthResult& result
        );
};