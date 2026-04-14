#include "HealthMapper.h"

void HealthMapper::toJson(char* buffer, size_t size, const HealthResult& result) {
    snprintf(buffer, size,
        "{"
            "\"chipInfo\":{"
                "\"model\":%u,"
                "\"cores\":%u,"
                "\"revision\":%u,"
                "\"features\":%u,"
                "\"wifi\":%d,"
                "\"ble\":%d,"
                "\"bluetooth\":%d,"
                "\"embeddedFlash\":%d,"
                "\"psRam\":%d"
            "},"
            "\"MemoryInfo\":{"
                "\"currentFreeHeap\":%u,"
                "\"minimumFreeHeap\":%u,"
                "\"defaultHeap\":%u,"
                "\"heap8bit\":%u,"
                "\"dmaHeap\":%u,"
                "\"internalHeap\":%u,"
                "\"psramHeap\":%u"
            "}"
        "}",
        (unsigned)result.chipInfo.model,
        (unsigned)result.chipInfo.cores,
        (unsigned)result.chipInfo.revision,
        (unsigned)result.chipInfo.features,
        result.chipInfo.wifi,
        result.chipInfo.ble,
        result.chipInfo.bluetooth,
        result.chipInfo.embeddedFlash,
        result.chipInfo.psRam,
        (unsigned)result.memoryInfo.currentFreeHeap,
        (unsigned)result.memoryInfo.minimumFreeHeap,
        (unsigned)result.memoryInfo.defaultHeap,
        (unsigned)result.memoryInfo.heap8bit,
        (unsigned)result.memoryInfo.dmaHeap,
        (unsigned)result.memoryInfo.internalHeap,
        (unsigned)result.memoryInfo.psramHeap
    );
}