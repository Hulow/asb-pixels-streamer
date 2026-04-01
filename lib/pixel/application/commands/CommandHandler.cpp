#include "CommandHandler.h"
#include "../../application/domain/Pixel.h"
#include "../../application/domain/Frame.h"

CommandHandler::CommandHandler(IConsumer& consumer) : _consumer(consumer) {}

void CommandHandler::execute(const Command& command) {
    Pixel pixel = Pixel::from(
        command.getGreen(),
        command.getRed(),
        command.getBlue()
    );

    Frame frame = Frame::from({});
    
    for (int i = 0; i < command.getPixelsCount(); i++) {
        frame.add(pixel);
    }

    _consumer.stream(frame);
}