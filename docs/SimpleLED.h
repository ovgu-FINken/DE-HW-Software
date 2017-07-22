#pragma once

#include "AbstractComponent.h"

class SimpleLED: public AbstractComponent {
public:
    /**
     * Simple blinking LED
     *
     * @param outPin - pin on board, where LED is connected
     */
    SimpleLED(PinName outPin);

    /**
     * Simple blinking LED
     *
     * @param outPin - pin on board, where LED is connected
     * @param initValue - init value of the LED, either -1 or 1
     */
    SimpleLED(PinName outPin, int initValue);

    virtual void update();

private:
    DigitalOut led;
};