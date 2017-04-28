#include "SimpleLED.h"
#include "mbed.h"

SimpleLED::SimpleLED(PinName outPin): led(outPin) {}

SimpleLED::SimpleLED(PinName outPin, int initValue): led(outPin, initValue) {}

void SimpleLED::update() {
    led = !led;
}

