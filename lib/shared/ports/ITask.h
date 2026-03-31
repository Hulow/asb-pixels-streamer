#pragma once

class ITask {
    public:
        virtual ~ITask() = default;
        virtual bool start() = 0;
        virtual void stop() = 0;
        
};