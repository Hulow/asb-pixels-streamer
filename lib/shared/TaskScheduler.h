#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "ITaskScheduler.h"

class TaskScheduler : public ITaskScheduler {
    private:
        TaskFunction_t _function;
        const char* _name;
        uint32_t _stackDepth = 4096;
        void* _params;
        UBaseType_t _priority = 5;
        TaskHandle_t _handle;
        StaticTask_t* _taskBuffer;
        StackType_t* _stackBuffer;
    public:
        TaskScheduler(
            TaskFunction_t function,
            const char* name,
            void* params
        );
        bool start() override;
        void stop() override;

        ~TaskScheduler() override {
            stop();
            delete[] _stackBuffer;
            delete _taskBuffer;
        }
};