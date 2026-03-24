#include "FrameConverter.h"

void FrameConverter::toSymbols(
    const Frame& frame,
    const Timing& timing,
    std::vector<Symbol>& outSymbols
) {
    // Clear the vector before filling
    outSymbols.clear();

    // Convert each Pixel in the frame to symbols
    for (const Pixel& pixel : frame.getPixels()) {
        auto bits = pixel.serializeColor(); // get color bits
        for (const uint8_t& bit : bits) {
            // Map each bit to a Symbol based on timing
            outSymbols.push_back(
                bit == 1
                    ? Symbol::from(timing.getLowTimeLineSignal(), timing.getHighTimeLineSignal())
                    : Symbol::from(timing.getLowTimeLineNoSignal(), timing.getHighTimeLineNoSignal())
            );
        }
    }

    // Add a reset symbol at the end to finalize the frame
    outSymbols.push_back(Symbol::from(timing.getLowResetDuration(), 0));
}