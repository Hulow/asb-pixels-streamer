#pragma once

class ITaskScheduler {
    public:
        virtual ~ITaskScheduler() = default;
        virtual bool start() = 0;
        virtual void stop() = 0;
        
};