#ifndef NEOPIXEL_H
#define NEOPIXEL_H
    extern bool tft_backlight;
    void initPixels();
    void rgb_neopixel(int r,int g, int b);
    void rgb_neopixel_on(int r,int g, int b);
    void rgb_neopixel_off();
#endif