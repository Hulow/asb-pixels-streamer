#pragma once

#include "esp_system.h"
#include <esp_chip_info.h>

#include "ChipInfoService.h"
#include "MemoryMonitor.h"

struct HealthResult {
    ChipInfo chipInfo;
    MemoryInfo memoryInfo;
};

class HealthService {
private:
    static ChipInfoService _chipInfoService;
    static MemoryMonitor _memoryMonitor;
    static HealthResult _result;

public:
    HealthResult monitor();
};