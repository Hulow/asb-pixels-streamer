#pragma once
#include <vector>
#include "Filter.h"
#include "../domain/IConsumer.h"
#include "../domain/Frame.h"

class Fading : public Filter {
private:
    float _step = 0.1; 
    std::vector<Pixel> _originalPixels;
    float _currentFactor = 0.0f;     
    bool _fadeIn = true;               

public:
    Fading(IConsumer& consumer) 
        : Filter(consumer) {}

    void stream(Frame& frame) override {
        if (_originalPixels.empty()) {
            _originalPixels = frame.getPixels();
        }

        for (size_t i = 0; i < frame.getPixels().size(); ++i) {
            frame.getPixels()[i].applyBrightness(_currentFactor);
        }

        _consumer.stream(frame);

        if (_fadeIn) {
            _currentFactor += _step;
            if (_currentFactor >= 1.0f) {
                _currentFactor = 1.0f;
                _fadeIn = false;
            }
        } else {
            _currentFactor -= _step;
            if (_currentFactor <= 0.0f) {
                _currentFactor = 0.0f;
                _fadeIn = true;
            }
        }
    }
};