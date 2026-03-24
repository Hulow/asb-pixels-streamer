#include "CommandHandler.h"
#include "Logger.h"
#include "domain/Pixel.h"
#include "domain/Color.h"
#include "domain/Symbol.h"
#include "domain/Sequence.h"
#include "domain/Timing.h"


#include "domain/services/FrameConverter.h"
#include <sstream>

CommandHandler::CommandHandler(Logger& logger, IPixelsStreamer& streamer)
    : _logger(logger), _streamer(streamer) {}

void CommandHandler::execute(const Command& command, std::function<void()> callBack) {
    std::vector<Pixel> pixels;
    std::vector<Symbol> symbols; 
    Timing timing(300, 1090, 1090, 320, 30000);           

    int totalLEDs = command.getPixelsCount();

    for (int i = 0; i < totalLEDs; ++i) {
        pixels.push_back(Pixel::from(Color::from(command.getGreen(), command.getRed(), command.getBlue())));

        Frame frame = Frame::from(pixels);
        FrameConverter::toSymbols(frame, timing, symbols);
        _streamer.stream(symbols);
      

    }

    if (callBack) callBack();
}