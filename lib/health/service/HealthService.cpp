#include "HealthService.h"
#include "esp_log.h"
#include <stdio.h>

ChipInfoService HealthService::_chipInfoService;

ChipInfo HealthService::monitor() {
    return _chipInfoService.getChipInfo();
}
