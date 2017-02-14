#pragma once

#include "mbed.h"
#include "PinNames.h"

class SimpleLED {
public:
    SimpleLED();
    void blink();
    void blink(int interval);
    void init();

private:
    DigitalOut led;
};