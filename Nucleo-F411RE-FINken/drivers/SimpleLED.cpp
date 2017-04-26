#include "SimpleLED.h"
#include "mbed.h"

SimpleLED::SimpleLED():led(LED1) {}

void SimpleLED::update() {
    led = !led;
}

