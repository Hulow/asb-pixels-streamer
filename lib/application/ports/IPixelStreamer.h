#pragma once

#include <functional>
#include "../domain/Symbol.h"

class IPixelsStreamer {
    public:
        virtual ~IPixelsStreamer() = default;
        virtual void stream(const std::vector<Symbol>& symbols) = 0;
        virtual void finish() = 0;
};