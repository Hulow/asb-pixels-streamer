#include "PixelConverter.h"

PixelConverter::PixelConverter(const Pixel& pixel) : _pixel(pixel) {
}

PixelConverter PixelConverter::fromPixel(const Pixel& pixel) {
    return PixelConverter(pixel);
}

std::vector<Symbol> PixelConverter::toSymbols() {
    _symbols.clear();
    for (const uint8_t& bit : _pixel.serializeColor() ) {
        _symbols.push_back(toSymbol(bit));
    }

    return _symbols;
}

Symbol PixelConverter::toSymbol(const uint8_t& bit) {
    return bit == 1
        ? Symbol::from(
            _pixel.getTiming().getLowTimeLineSignal(), 
            _pixel.getTiming().getHighTimeLineSignal())
        : Symbol::from(
            _pixel.getTiming().getLowTimeLineNoSignal(), 
            _pixel.getTiming().getHighTimeLineNoSignal()
        );
}