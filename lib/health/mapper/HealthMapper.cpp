#include "HealthMapper.h"

void HealthMapper::toJson(char* buffer, size_t size, const ChipInfo& chip) {
    snprintf(buffer, size,
        "{"
            "\"model\":%" PRIu32 ","
            "\"cores\":%" PRIu32 ","
            "\"revision\":%" PRIu32 ","
            "\"features\":%" PRIu32 ","
            "\"wifi\":%d,"
            "\"ble\":%d,"
            "\"bluetooth\":%d,"
            "\"embeddedFlash\":%d,"
            "\"psRam\":%d"
        "}",
        chip.model,
        chip.cores,
        chip.revision,
        chip.features,
        chip.wifi,
        chip.ble,
        chip.bluetooth,
        chip.embeddedFlash,
        chip.psRam
    );
}