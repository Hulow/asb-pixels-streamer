#pragma once
#include "../Pixel.h"
#include "../Symbol.h"
#include "../Frame.h"
#include "../Timing.h"
#include <vector>

/**
 * FrameConverter
 * ----------------
 * Converts a Frame (collection of Pixels) into a vector of Symbols
 * ready to be streamed to LEDs.
 * Stateless design: no internal buffers, safe for progressive LED sequences.
 */
class FrameConverter {
public:
    /**
     * Convert a frame into a vector of Symbols.
     * @param frame: the frame to convert
     * @param timing: timing configuration for LED signals
     * @param outSymbols: preallocated vector to store the output symbols
     */
    static void toSymbols(
        const Frame& frame,
        const Timing& timing,
        std::vector<Symbol>& outSymbols
    );
};