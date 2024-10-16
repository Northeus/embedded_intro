// https://stackoverflow.com/questions/24152553/hsv-to-rgb-and-back-without-floating-point-math-in-python

#ifndef HSV_RGB_H_
#define HSV_RGB_H_

#include <stdint.h>

typedef struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} Color;

Color HSVtoRGB(int16_t hue, int16_t saturation, int16_t value) {
    if (saturation == 0) {
        return (Color) {.r = value, .g = value, .b = value};
    }

    int16_t region = hue / 43;

    int16_t remainder = (hue - (region * 43)) * 6;

    int16_t P = (value * (255 - saturation)) >> 8;
    int16_t Q = (value * (255 - ((saturation * remainder) >> 8))) >> 8;
    int16_t T = (value * (255 - ((saturation * (255 - remainder)) >> 8))) >> 8;

    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;

    switch (region) {
        case 0:
            red = (uint8_t) value;
            green = (uint8_t) T;
            blue = (uint8_t) P;

            break;
        case 1:
            red = (uint8_t) Q;
            green = (uint8_t) value;
            blue = (uint8_t) P;

            break;
        case 2:
            red = (uint8_t) P;
            green = (uint8_t) value;
            blue = (uint8_t) T;

            break;
        case 3:
            red = (uint8_t) P;
            green = (uint8_t) Q;
            blue = (uint8_t) value;

            break;
        case 4:
            red = (uint8_t) T;
            green = (uint8_t) P;
            blue = (uint8_t) value;

            break;
        default:
            red = (uint8_t) value;
            green = (uint8_t) P;
            blue = (uint8_t) Q;
    }

  return (Color) {.r = red, .g = green, .b = blue};
}

#endif /* HSV_RGB_H_ */

