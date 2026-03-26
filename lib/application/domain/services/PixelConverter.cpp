#include "PixelConverter.h"

PixelConverter::PixelConverter(const Pixel& pixel, const Timing& timing) : _pixel(pixel), _timing(timing) {
}

PixelConverter PixelConverter::from(const Pixel& pixel, const Timing& timing) {
    return PixelConverter(pixel, timing);
}

std::vector<Symbol> PixelConverter::toSymbols() {
    _symbols.clear();
    // for (const uint8_t& bit : _pixel.serializeColor() ) {
    //     _symbols.push_back(toSymbol(bit));
    // }

    return _symbols;
}

Symbol PixelConverter::toSymbol(const uint8_t& bit) {
    return bit == 1
        ? Symbol::from(
            _timing.getLowTimeLineSignal(), 
            _timing.getHighTimeLineSignal())
        : Symbol::from(
            _timing.getLowTimeLineNoSignal(), 
            _timing.getHighTimeLineNoSignal()
        );
}

void PixelConverter::addResetTiming() {
     _symbols.push_back(Symbol::from(_timing.getLowResetDuration(), 0));
}

