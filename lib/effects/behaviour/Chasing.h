#pragma once

#include <vector>

#include "Behaviour.h"
#include "../core/IConsumer.h"
#include "../core/Pixel.h"


class Chasing : public Behaviour {  
    private:
        State _state;

    public:
        Chasing(
            IConsumer& consumer, 
            const State& state = {}
        )
            : 
                Behaviour(consumer), 
                _state(state)
            {}
        
        void stream(const std::vector<Pixel> pixels) {}
};