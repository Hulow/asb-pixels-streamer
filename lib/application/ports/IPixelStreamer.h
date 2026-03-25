#pragma once

#include <functional>
#include "../domain/Symbol.h"
#include <driver/rmt_tx.h>


class IPixelsStreamer {
    public:
        virtual ~IPixelsStreamer() = default;
        virtual void stream(const std::vector<Symbol>& symbols) = 0;
        virtual rmt_channel_handle_t getChannelHandle() = 0;
         virtual void test() = 0;
};