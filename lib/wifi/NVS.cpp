#include "NVS.h"


/*
Non-volatile storage library
https://docs.espressif.com/projects/esp-idf/en/release-v5.3/esp32/api-reference/storage/nvs_flash.html
    - Initialize the default NVS partition.
*/

void NVS::init() {
    ESP_ERROR_CHECK(nvs_flash_init());
}