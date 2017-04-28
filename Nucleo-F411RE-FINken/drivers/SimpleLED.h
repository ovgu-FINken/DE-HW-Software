#pragma once

#include "AbstractComponent.h"

class SimpleLED: public AbstractComponent {
public:
    SimpleLED(PinName outPin);
    SimpleLED(PinName outPin, int initValue);
    virtual void update();

private:
    DigitalOut led;
};