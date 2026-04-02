#include "CommandHandler.h"
#include "../domain/Pixel.h"
#include "../domain/Frame.h"

CommandHandler::CommandHandler(IConsumer& consumer,  ITimer& timer) : _consumer(consumer), _timer(timer) {}

void CommandHandler::execute(const Command& command) {
    Frame frame;
    int frameIndex = 0;
    const int sequenceLength = command.getSequenceLength();

    Pixel pixel = Pixel::from(
        command.getGreen(),
        command.getRed(),
        command.getBlue()
    );
    
    for (int i = 0; i < sequenceLength; i++) {
        frame.add(pixel);
    }

    while(true) {
        _consumer.stream(frame);
        _timer.wait(100);
        frameIndex = (frameIndex + 1) % sequenceLength;
    }
}