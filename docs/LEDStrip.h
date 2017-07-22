#pragma once

#include "../AbstractComponent.h"
#include "WS2812.h"
#include "PixelArray.h"
#include "../UARTMessenger.h"

class LEDStrip : public AbstractComponent {
public:
    /**
     * @param uartMsngr UARTMessenger object for communicating with Paparazzi
     * @param pin Output pin. Connect to "Din" on the first WS2812 in the strip
     * @param size Number of LEDs in your strip
     * @param zeroHigh How many NOPs to insert to ensure TOH is properly generated. See library description for more information.
     * @param zeroLow How many NOPs to insert to ensure TOL is properly generated. See library description for more information.
     * @param oneHigh How many NOPs to insert to ensure T1H is properly generated. See library description for more information.
     * @param oneLow How many NOPs to insert to ensure T1L is properly generated. See library description for more information.
     */
    LEDStrip(UARTMessenger *const uartMsngr, PinName pin, int size, int zeroHigh, int zeroLow, int oneHigh, int oneLow);

    /**
     * @param mode one of predifined modes
     */
    void setMode(uint8_t mode);

    /**
     * @param color color in RGB format, e.g. 0x00FF00
     */
    void setColor(unsigned int color);

    /**
     * @param color color in RGB format, e.g. 0x00FF00
     * @param led id of the LED to use
     */
    void setColor(unsigned int color, uint8_t led=0);

    virtual void update();

    /**
     * @param msg message struct from Paparazzi
     */
    virtual void onPaparazziMsg(SubMessage *msg);

private:
    UARTMessenger *const uartMessenger;
    SubMessage subMessage;
    WS2812 ws;
    PixelArray px;
    int stripSize;
    int offset;
    uint8_t mode;
};
