#pragma once
#include <cstdint>
#include "Command.h"
#include <functional> 
#include "../ports/IPixelWaveFormPipeline.h"

class CommandHandler {
    private:
        uint8_t _pixel;
        IPixelWaveFormPipeline& _pipeline;
    
    public:
        CommandHandler(IPixelWaveFormPipeline& pipeline);
        void execute(const Command& command, std::function<void()> callBack);
};