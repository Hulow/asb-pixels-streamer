#include "TaskScheduler.h"

TaskScheduler::TaskScheduler(TaskFunction_t function, const char* name, void* params) 
    : 
        _function(function),
        _name(name),
        _params(params),
        _handle(nullptr)
    {}

bool TaskScheduler::start() {
    _handle = xTaskCreateStatic(
        _function,
        _name,
        STACK_SIZE,
        _params,
        _priority,
        _stackBuffer,
        &_taskBuffer
    );

    return (_handle != nullptr);
}

void TaskScheduler::stop() {
    if (_handle) {
        vTaskDelete(_handle);
        _handle = nullptr;
    };
}
