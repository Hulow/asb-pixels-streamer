#include "CommandHandler.h"
#include "domain/Pixel.h"

CommandHandler::CommandHandler(IPixelWaveFormPipeline& pipeline)
    : _pipeline(pipeline) {}

void CommandHandler::execute(const Command& command, std::function<void()> callBack) {
    for (int i = 0; i < command.getPixelsCount(); ++i) {
        _pipeline.enqueuePixel(
            Pixel::from(
                command.getGreen(), 
                command.getRed(), 
                command.getBlue()
            )
        );
    }
    _pipeline.signalLastPixel();
    _pipeline.start();

    if (callBack) callBack();
}