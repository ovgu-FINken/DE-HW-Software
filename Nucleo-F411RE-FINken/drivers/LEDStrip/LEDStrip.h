#pragma once

#include "../AbstractComponent.h"
#include "mbed.h"
#include "PinNames.h"

class LEDStrip: public AbstractComponent {
public:
    LEDStrip(PinName pin, int size, int zeroHigh, int zeroLow, int oneHigh, int oneLow);
    virtual void update();

private:
    WS2812 ws;
    PixelArray px;
    int stripSize;
    int r_offset;
    int g_offset;
    int b_offset;
};