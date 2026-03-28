#pragma once

#include "../core/IConsumer.h"

struct State {
    int currentPixel;
    int pixelsCount;
    int chasingLength ;
};

class Behaviour : public IConsumer {
    protected:
        IConsumer& _consumer; 
    public: 
        Behaviour(IConsumer& consumer) : _consumer(consumer) {}
        
        virtual ~Behaviour() = default;

        virtual void pushPixel(Pixel& pixel) = 0;

        virtual void start() override {
            _consumer.start();
        }

        virtual void pushResetSignal() override {
            _consumer.pushResetSignal();
        }

        virtual void setState(const State& state) = 0;
};