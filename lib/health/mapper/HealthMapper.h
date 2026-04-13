#pragma once

#include <cstddef>
#include <inttypes.h>

#include "../service/ChipInfoService.h"


class HealthMapper {
    public:
        static void toJson(
            char* buffer, 
            size_t size, 
            const ChipInfo& chip
        );
};