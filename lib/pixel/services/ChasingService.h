#pragma once

#include "../commands/CommandHandler.h"
#include "../../shared/TaskScheduler.h"

class ChasingService {
private:
    CommandHandler& _handler;
    TaskScheduler _scheduler;
    static void runTask(void* arg);

public:
    ChasingService(CommandHandler& handler, const char* name);
    void start();
    void stop();
};