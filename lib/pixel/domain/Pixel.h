#pragma once
#include <cstdint>
#include <array>

class Pixel {
    private:
        uint8_t _green;
        uint8_t _red;
        uint8_t _blue;
        Pixel(const uint8_t& green, const uint8_t& red, const uint8_t& blue) : _green(green), _red(red), _blue(blue) {}

        void setGreen(const uint8_t& green) {
            _green = green;
        };

        void setRed(const uint8_t& red) {
            _red = red;
        };

        void setBlue(const uint8_t& blue) {
            _blue = blue;
        };

    public: 
        static Pixel from(const uint8_t& green, const uint8_t& red, const uint8_t& blue) {
            return Pixel(green, red, blue);
        }

        uint8_t getGreen() const {
            return _green;
        }

        uint8_t getRed() const {
            return _red;
        }

        uint8_t getBlue() const {
            return _blue;
        }

        void turnOff() {
            setGreen(0);
            setRed(0);
            setBlue(0);
        };

        void applyBrightness(const float& factor) {
            setGreen(_green * factor);
            setRed(_red * factor);
            setBlue(_blue * factor);
        }

        std::array<uint8_t, 3> toBytes() const { 
            return {
                _green, 
                _red, 
                _blue
            }; 
        }
};