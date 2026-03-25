#include "CommandHandler.h"
#include "Logger.h"
#include "domain/Pixel.h"
#include "domain/Color.h"
#include "domain/Symbol.h"
#include "domain/Sequence.h"
#include "domain/Timing.h"
#include "domain/Frame.h"



#include "domain/services/PixelConverter.h"
#include <sstream>

CommandHandler::CommandHandler(Logger& logger, IPixelsStreamer& streamer)
    : _logger(logger), _streamer(streamer) {}

void CommandHandler::execute(const Command& command, std::function<void()> callBack) {
    std::vector<Pixel> pixels;
    std::vector<Symbol> symbols; 
    Timing timing(300, 1090, 1090, 320, 30000);           

    int totalLEDs = command.getPixelsCount();

    Sequence sequence;
    std::vector<Frame> frames;
    Frame frame = Frame::from({});
    frame.reserve(totalLEDs);

    for (int i = 0; i < totalLEDs; ++i) {
        PixelConverter converter = 
            PixelConverter::from(
                Pixel::from(
                    Color::from(
                        command.getGreen(), 
                        command.getRed(), 
                        command.getBlue()
                    )
                ),
                timing
        );
        frame.addSymbols(converter.toSymbols());
        // frame.add(Symbol::from(timing.getLowResetDuration(), 0));
        // frames.push_back(frame);
        // sequence.add(frame);
        _logger.info("frame with items", std::to_string(frame.getSymbols().size()));
        // frame.clear();
    }
    _streamer.stream(frame.getSymbols());


    // for (auto& frame : sequence.getFrames()) {
    //     _logger.info("frame with items", std::to_string(frame.getSymbols().size()));
    //     _streamer.stream(frame.getSymbols());
    // }

    if (callBack) callBack();
}