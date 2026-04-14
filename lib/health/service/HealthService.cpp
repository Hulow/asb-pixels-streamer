#include "HealthService.h"
#include "esp_log.h"
#include <stdio.h>

ChipInfoService HealthService::_chipInfoService;
MemoryMonitor HealthService::_memoryMonitor;
HealthResult HealthService::_result;

HealthResult HealthService::monitor() {
    return {
        chipInfo: _chipInfoService.getChipInfo(),
        memoryInfo: _memoryMonitor.getMemoryInfo()
    };
}
