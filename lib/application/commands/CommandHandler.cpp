#include "CommandHandler.h"
#include "Logger.h"
#include "domain/Pixel.h"
#include "domain/Color.h"
#include "domain/Symbol.h"
#include "domain/Sequence.h"
#include "domain/Timing.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "domain/services/PixelConverter.h"
#include <sstream>

CommandHandler::CommandHandler(Logger& logger, IPixelsStreamer& streamer)
    : _logger(logger), _streamer(streamer) {}

void CommandHandler::execute(const Command& command, std::function<void()> callBack) {
    std::vector<Pixel> pixels;
    std::vector<Symbol> symbols; 
    Timing timing(300, 1090, 1090, 320, 30000);           

    int totalLEDs = command.getPixelsCount();
    std::vector<Symbol> allSymbols;
    for (int i = 0; i < totalLEDs; ++i) {
        PixelConverter converter = 
            PixelConverter::from(
                Pixel::from(
                        command.getGreen(), 
                        command.getRed(), 
                        command.getBlue()
                    
                ),
                timing
            );
            _streamer.addSymbolsToQueue(
                _streamer.toRmtSymbols(
                    converter.toSymbols()
                )
            );
    }
   
    _streamer.addSymbolsToQueue(
        _streamer.toRmtSymbols({ Symbol::from(30000, 0) })
    );

    _streamer.stream();

    if (callBack) callBack();
}