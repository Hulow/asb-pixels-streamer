#pragma once

#include <stdio.h>
#include <esp_chip_info.h>

struct ChipInfo {
    uint32_t model;
    uint32_t cores;
    uint32_t revision;
    uint32_t features;
    bool wifi;
    bool ble;
    bool bluetooth;
    bool embeddedFlash;
    bool psRam;
};

class ChipInfoService {
    private: 
        ChipInfo _chipInfo;
        void scanChip();

    public: 
        ChipInfoService();
        ChipInfo getChipInfo();
};