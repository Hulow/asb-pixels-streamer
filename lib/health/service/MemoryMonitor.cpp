#include "MemoryMonitor.h"
#include "esp_log.h"
#include <esp_heap_caps.h>

MemoryMonitor::MemoryMonitor() {
    monitor();
}

void MemoryMonitor::monitor() {
    _info.currentFreeHeap = esp_get_free_heap_size();
    _info.minimumFreeHeap = esp_get_minimum_free_heap_size();
    _info.defaultHeap = heap_caps_get_free_size(MALLOC_CAP_DEFAULT);
    _info.heap8bit = heap_caps_get_free_size(MALLOC_CAP_8BIT);
    _info.dmaHeap =  heap_caps_get_free_size(MALLOC_CAP_DMA);
    _info.internalHeap = heap_caps_get_free_size(MALLOC_CAP_INTERNAL);
    _info.psramHeap = heap_caps_get_free_size(MALLOC_CAP_SPIRAM);
}

const MemoryInfo MemoryMonitor::getMemoryInfo() const {
    return _info;
}