#include "SimpleLED.h"
#include "mbed.h"

SimpleLED::SimpleLED():led(LED1) {}

void SimpleLED::init() {
    //this->led(LED1);
}

void SimpleLED::blink(int interval)  {
    led = !led;
    Thread::wait(interval);
}

void SimpleLED::blink() {
    led = !led;
}

