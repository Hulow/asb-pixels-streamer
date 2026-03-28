#pragma once
#include "Behaviour.h"
#include "../core/IConsumer.h"
#include "../core/Pixel.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


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
        void enqueuePixel(Pixel& pixel) override {
            for (int i = 1; i <= _state.pixelsCount; i++) {
                if (i <= _state.currentPixel) {
                    Pixel p = Pixel::from(0, 255, 0);
                    // ESP_LOGI("Chasing", "LED %d ON from Sequence %d Color: %d. %d, %d", i,  _state.currentPixel, pixel.getGreen(), pixel.getRed(), pixel.getBlue());
                    _consumer.enqueuePixel(p);
                } else {
                    Pixel off = Pixel::from(0, 0, 0);
                    _consumer.enqueuePixel(off);
                }
                // ESP_LOGI("Chasing", "Pixel %d from Sequence %d", i, _state.currentPixel);

            }
            // vTaskDelay(pdMS_TO_TICKS(10));   
        }   

        void setState(const State& state) override {
            _state = state;
        }
};