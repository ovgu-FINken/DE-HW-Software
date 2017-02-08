#ifndef NUCLEO_F411RE_TEST_LEDS_H
#define NUCLEO_F411RE_TEST_LEDS_H

#include "mbed.h"

class SimpleLED {
public:
    void blink();
    void blink(int interval);
    void init();

private:
    DigitalOut led(LED1);
};

#endif