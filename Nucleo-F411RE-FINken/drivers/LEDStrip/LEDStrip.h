#pragma once

#include "../AbstractComponent.h"
#include "mbed.h"
#include "PinNames.h"
#include "WS2812.h"
#include "PixelArray.h"

class LEDStrip : public AbstractComponent {
public:
     /**
      * Constructor for creating a new LED Strip
      *
      * @param pin Output pin. Connect to "Din" on the first WS2812 in the strip
      * @param size Number of LEDs in your strip
      * @param zeroHigh How many NOPs to insert to ensure TOH is properly generated. See library description for more information.
      * @param zeroLow How many NOPs to insert to ensure TOL is properly generated. See library description for more information.
      * @param oneHigh How many NOPs to insert to ensure T1H is properly generated. See library description for more information.
      * @param oneLow How many NOPs to insert to ensure T1L is properly generated. See library description for more information.
      */
    LEDStrip(PinName pin, int size, int zeroHigh, int zeroLow, int oneHigh, int oneLow);

    /**
     * Set LED Strip to manual control instead of getting control action from paparazzi, which is set by default
     *
     * @param mode one of predifined modes
     */
    void setMode(uint8_t mode);

    virtual void update();

    virtual void onPaparazziMsg();

private:
    WS2812 ws;
    PixelArray px;
    int stripSize;
    int r_offset;
    int g_offset;
    int b_offset;
    uint8_t mode;
};