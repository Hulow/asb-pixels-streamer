#include "ChipInfoService.h"

ChipInfoService::ChipInfoService() {
    scanChip();
}

void ChipInfoService::scanChip() {
    esp_chip_info_t info;
    esp_chip_info(&info);

    _chipInfo.wifi = info.features & CHIP_FEATURE_WIFI_BGN;
    _chipInfo.ble = info.features & CHIP_FEATURE_BLE;
    _chipInfo.bluetooth = info.features & CHIP_FEATURE_BT;
    _chipInfo.embeddedFlash = info.features & CHIP_FEATURE_EMB_FLASH;
    _chipInfo.psRam = info.features & CHIP_FEATURE_EMB_PSRAM;
    _chipInfo.model = info.model;
    _chipInfo.cores = info.cores;
    _chipInfo.revision = info.revision;
    _chipInfo.features = info.features;
}

ChipInfo ChipInfoService::getChipInfo() {
    return _chipInfo;
}