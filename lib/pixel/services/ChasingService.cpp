#include "ChasingService.h"

ChasingService::ChasingService(CommandHandler& handler, const char* name) : 
    _handler(handler), 
    _scheduler(
        runTask, 
        name, 
        this
    )
{}

void ChasingService::runTask(void* arg) {
    auto self = static_cast<ChasingService*>(arg);
    Command command = Command::from(255, 255, 0, 13);
    self->_handler.execute(command);
}

void ChasingService::start() {
    _scheduler.start();
}

void ChasingService::stop() {
    _scheduler.stop();
}