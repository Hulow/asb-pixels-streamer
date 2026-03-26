#include "CommandHandler.h"
#include "domain/Pixel.h"

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
    _pipeline.addResetToQueue();
    _pipeline.startConsuming();

    if (callBack) callBack();
}