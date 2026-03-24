#include "CommandHandler.h"
#include "Logger.h"
#include "domain/Pixel.h"
#include "domain/Color.h"
#include "domain/Sequence.h"
#include "domain/services/FrameConverter.h"
#include <sstream>

CommandHandler::CommandHandler(Logger& logger, IPixelsStreamer& streamer) : _logger(logger), _streamer(streamer) {}

void CommandHandler::execute(const Command& command, std::function<void()> callBack) {
    std::vector<Pixel> pixels;
    for (int i = 0; i < command.getPixelsCount(); ++i) {
        pixels.push_back(
            Pixel::from(
                Color::from(
                    command.getGreen(), 
                    command.getRed(), 
                    command.getBlue()
                )
            )
        );
        FrameConverter symbols = FrameConverter::from(Frame::from(pixels));
        _streamer.stream(symbols.toSymbols());

    }

}