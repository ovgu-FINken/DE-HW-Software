#pragma once

#include "../AbstractComponent.h"
#include "WS2812.h"
#include "PixelArray.h"
#include "UARTMessenger.h"
#include "../UARTMessenger.h"

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
    LEDStrip(UARTMessenger *const uartMsngr, PinName pin, int size, int zeroHigh, int zeroLow, int oneHigh, int oneLow);

    /**
     * Set LED Strip to manual control instead of getting control action from paparazzi, which is set by default
     *
     * @param mode one of predifined modes
     */
    void setMode(uint8_t mode);

    /**
     * Set color to LED Strip
     *
     * @param color color in RGB format, e.g. 0x00FF00
     */
    void setColor(unsigned int color);

    virtual void update();

    /**
     * Reaction on the message from Paparazzi.
     * Expected message structure: type (1 byte), id (1 byte), length (1 byte), data (length byte)
     * Data structure: led id (1 byte), red channel (1 byte), green channel (1 byte), blue channel (1 byte)
     *
     * @param msg SubMessage came from Paparazzi
     */
    virtual void onPaparazziMsg(SubMessage* msg);

private:
    UARTMessenger *const uartMessenger;
    SubMessage subMessage;
    WS2812 ws;
    PixelArray px;
    int stripSize;
    int offset;
    uint8_t mode;
};
