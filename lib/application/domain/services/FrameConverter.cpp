#include "FrameConverter.h"

FrameConverter::FrameConverter(
    const Frame& frame, 
    const Timing& timing
) : 
    _frame(frame), 
    _timing(timing) 
{}

FrameConverter FrameConverter::from(const Frame& frame) {
    return FrameConverter(frame);
}

std::vector<Symbol> FrameConverter::toSymbols() {
    _symbols.clear();
    for (const Pixel& pixel : _frame.getPixels() ) {
        toSymbol(pixel);
    }

    reset();

    return _symbols;
}

void FrameConverter::toSymbol(const Pixel& pixel) {
    for (const uint8_t& bit : pixel.serializeColor() ) {
        _symbols.push_back(
            mapSymbol(bit)
        );
    }
}

Symbol FrameConverter::mapSymbol(const uint8_t& bit) {
    return bit == 1
        ? Symbol::from(
            _timing.getLowTimeLineSignal(), 
            _timing.getHighTimeLineSignal())
        : Symbol::from(
            _timing.getLowTimeLineNoSignal(), 
            _timing.getHighTimeLineNoSignal()
        );
}

void FrameConverter::reset() {
    _symbols.push_back(Symbol::from(_timing.getLowResetDuration(), 0));
}
