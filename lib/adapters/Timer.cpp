#include "Timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void Timer::wait(const uint32_t& ms) {
    vTaskDelay(pdMS_TO_TICKS(ms));
}