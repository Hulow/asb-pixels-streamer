#pragma once
#include "Filter.h"
#include "../domain/Pixel.h"
#include "../domain/Frame.h"

class Chasing : public Filter {  
private:
    int _currentIndex = 0; 
    const int chaseLength = 3;
    Pixel _pixelOff = Pixel::from(0, 0, 0);
    Pixel _pixelOn = Pixel::from(0, 255, 0);

public:
    Chasing(IConsumer& consumer): Filter(consumer) {}

    void stream(Frame& frame) override {
        int size = frame.getPixels().size();

        // turn off pixel that left the chase window
        int offIndex = (_currentIndex - chaseLength + size) % size;
        frame.getPixels()[offIndex] = _pixelOff;

        // turn on all pixels in the chase window
        for (int i = 0; i < chaseLength; i++) {
            int index = (_currentIndex - i + size) % size;
            frame.getPixels()[index] = _pixelOn;
        }

        _consumer.stream(frame); // send to next decorator / transmitter

        _currentIndex = (_currentIndex + 1) % size;
    }
};