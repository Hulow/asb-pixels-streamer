#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "ITaskScheduler.h"

static constexpr uint32_t STACK_SIZE = 4096;

class TaskScheduler : public ITaskScheduler {
    private:
        TaskFunction_t _function;
        const char* _name;
        void* _params;
        UBaseType_t _priority = 5;
        TaskHandle_t _handle;
        StaticTask_t _taskBuffer;
        StackType_t _stackBuffer[STACK_SIZE];
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
        }
};