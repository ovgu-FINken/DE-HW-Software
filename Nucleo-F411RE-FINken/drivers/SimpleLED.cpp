#include "SimpleLED.h"
#include "mbed.h"

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

