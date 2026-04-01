#pragma once

#include "Filter.h"
#include "../domain/IConsumer.h"
#include "../domain/Pixel.h"
#include "../domain/Frame.h"

class Chasing : public Filter {  
    public:
        Chasing(IConsumer& consumer, ITimer& timer): Filter(consumer, timer) {}
        void stream(Frame& frame) override {

            Pixel pixelOn = Pixel::from(0, 255, 0);
            Pixel pixelOff = Pixel::from(0, 0, 0);

            const int chaseLength = 4;
            const int pixelthreshold = chaseLength - 1;

            for (int i = 0; i < frame.getPixels().size() ; i ++) {
                if(shouldTurnOff(i, chaseLength)) {
                    turnOff(frame, i - chaseLength, pixelOff);
                }

                turnOn(frame, i, pixelOn);

                _consumer.stream(frame);
                _timer.wait(100);
            }
        }
    private:
        bool shouldTurnOff(int currentIndex, int chaseLength) const {
            return currentIndex >= chaseLength;
        }

        void turnOff(Frame& frame, int index, const Pixel& pixelOff) const {
            frame.getPixels()[index] = pixelOff;
        }

        void turnOn(Frame& frame, int index, const Pixel& pixelOn) const {
            frame.getPixels()[index] = pixelOn;
        }
};