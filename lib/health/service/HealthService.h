#pragma once

#include "esp_system.h"
#include <esp_chip_info.h>

#include "ChipInfoService.h"

class HealthService {
private:
    static ChipInfoService _chipInfoService;

public:
    ChipInfo monitor();
};