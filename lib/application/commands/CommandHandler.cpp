#include "CommandHandler.h"
#include "Logger.h"
#include "domain/Pixel.h"
#include "domain/Color.h"
#include "domain/Sequence.h"
#include "domain/services/PixelConverter.h"
#include <sstream>

CommandHandler::CommandHandler(Logger& logger, IPixelsStreamer& streamer) : _logger(logger), _streamer(streamer) {}

void CommandHandler::execute(const Command& command, std::function<void()> callBack) {
    // std::stringstream ss;
    // ss << "Executed with pixel: " << static_cast<int>(command.getPixelsCount());
    // _logger.info("CommandHandler", ss.str());

    // callBack();

    Sequence sequence(command.getPixelsCount());
    for (int i = 0; i < command.getPixelsCount(); ++i) {
        sequence.add(
            Pixel::from(
                Color::from(
                    command.getGreen(), 
                    command.getRed(), 
                    command.getBlue()
                )
            )
        );
        PixelConverter symbols = PixelConverter::fromPixel(sequence.getPixel(i));
        _streamer.stream(symbols.toSymbols());
    }
}