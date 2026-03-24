#pragma once
#include <vector>
#include "Frame.h"

class Sequence {
    private:
        std::vector<Frame> _frames = {};
    public:
        Sequence() = default;

        void add(const Frame& frame) {
            _frames.push_back(frame);
        }

        std::vector<Frame> getFrames() {
            return _frames;
        }
};