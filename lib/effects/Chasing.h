#pragma once
#include "Behaviour.h"
#include "../core/IConsumer.h"
#include "../core/Pixel.h"



// which led from the strip
// how long is the chase
// speed (time)
// blackpixel

struct ChasingState {
    int currentPixel;
    int pixelCount;
    int chasingLength ;
};

class Chasing : public Behaviour{  
    private:
        ChasingState _state;

        void setCurrentPixel(const int& currentPixel) {
            _state.currentPixel = currentPixel;
        };

        void setPixelCount(const int& pixelCount) {
            _state.pixelCount = pixelCount;
        };

        void setChasingLength(const int& chasingLength) {
            _state.chasingLength = chasingLength;
        };

    public:
        Chasing(
            IConsumer& consumer, 
            const ChasingState& state = {}
        )
            : 
                Behaviour(consumer), 
                _state(state)
            {}
        void enqueuePixel(Pixel& pixel) override {
            for (int i = 0; i < _state.pixelCount; i++ ) {
                // if (i < _pixelNumber - _pixelLength) {
                //     _consumer.enqueuePixel(Pixel::from(0, 0, 0));
                // }

                // if((_pixelNumber - _pixelLength) > i > _pixelNumber) {
                //     _consumer.enqueuePixel(pixel);
                // }

                // if(i > _pixelNumber) {
                //     _consumer.enqueuePixel(Pixel::from(0, 0, 0));
                // }
            }
        }

        void setState(const ChasingState& state) {
            setChasingLength(state.chasingLength);
            setCurrentPixel(state.currentPixel);
            setPixelCount(state.pixelCount);
        }
};