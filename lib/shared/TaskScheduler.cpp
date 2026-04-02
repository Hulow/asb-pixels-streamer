#include "TaskScheduler.h"

TaskScheduler::TaskScheduler(TaskFunction_t function, const char* name, void* params) 
    : 
        _function(function),
        _name(name),
        _params(params),
        _handle(nullptr)
    {}

bool TaskScheduler::start() {
    /* store a stack control block */
    _taskBuffer = new StaticTask_t; 
    /* store a task's stack */
    _stackBuffer = new StackType_t[_stackDepth]; 

    _handle = xTaskCreateStatic(
        _function,
        _name,
        _stackDepth,
        _params,
        _priority,
        _stackBuffer,
        _taskBuffer
    );

    return (_handle != nullptr);
}

void TaskScheduler::stop() {
    if (_handle) {
        vTaskDelete(_handle);
        _handle = nullptr;
    };
}
