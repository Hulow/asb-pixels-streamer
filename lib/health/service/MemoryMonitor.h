#pragma once

#include "esp_system.h"

struct MemoryInfo {
    uint32_t currentFreeHeap; /* how much memory is free right now */
    uint32_t minimumFreeHeap; /* the lowest amount of free memory the program ever had, detect leaks */
    size_t defaultHeap; /* free memory in the main heap used by most allocations */
    size_t heap8bit; /* memory that can be used normally for most variables and data */
    size_t dmaHeap; /* memory that hardware peripherals can directly access */
    size_t internalHeap; /* memory inside the ESP32 chip (fast and preferred) */
    size_t psramHeap; /* extra external memory (PSRAM) / I dont have this RAM*/
};

class MemoryMonitor {

    private:   
        MemoryInfo _info;
        void monitor();

    public:
        MemoryMonitor();
        const MemoryInfo getMemoryInfo() const;
};