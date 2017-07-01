#pragma once

#include "../AbstractComponent.h"
#include "WS2812.h"
#include "PixelArray.h"
#include "UARTMessenger.h"
#include "../UARTMessenger.h"

class LEDStrip : public AbstractComponent {
public:
     
    LEDStrip(UARTMessenger *const uartMsngr, PinName pin, int size, int zeroHigh, int zeroLow, int oneHigh, int oneLow);

    /**
     * Set LED Strip to manual control instead of getting control action from paparazzi, which is set by default
    
     */
    void setMode(uint8_t mode);

    /**
     * Set color to LED Strip
     
     */
    void setColor(unsigned int color);

    virtual void update();

    /**
     * Reaction on the message from Paparazzi.
     
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
