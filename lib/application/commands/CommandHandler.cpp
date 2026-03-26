#include "CommandHandler.h"
#include "domain/Pixel.h"
#include "domain/Symbol.h"
#include "domain/Sequence.h"
#include "domain/Timing.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "domain/services/PixelConverter.h"
#include <sstream>

CommandHandler::CommandHandler(IPixelWaveFormPipeline& pipeline)
    : _pipeline(pipeline) {}

void CommandHandler::execute(const Command& command, std::function<void()> callBack) {
    for (int i = 0; i < command.getPixelsCount(); ++i) {
        _pipeline.addPixelToQueue(
            Pixel::from(
                command.getGreen(), 
                command.getRed(), 
                command.getBlue()
            )
        );
    }

    _pipeline.startConsuming();

    if (callBack) callBack();
}