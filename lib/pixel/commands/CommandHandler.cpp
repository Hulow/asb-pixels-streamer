#include "CommandHandler.h"
#include "../domain/Pixel.h"
#include "../domain/Frame.h"

CommandHandler::CommandHandler(IConsumer& consumer,  ITimer& timer) : _consumer(consumer), _timer(timer) {}

void CommandHandler::execute(const Command& command) {
    const int sequenceLength = command.getSequenceLength();
    Frame frame;

    Pixel pixel = Pixel::from(
        command.getGreen(),
        command.getRed(),
        command.getBlue()
    );
    
    for (int i = 0; i < sequenceLength; i++) {
        frame.add(pixel);
    }

    _consumer.stream(frame);
}