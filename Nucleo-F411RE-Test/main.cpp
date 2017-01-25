#include "mbed.h"

DigitalOut  led(LED1);
Serial pc(USBTX, USBRX); //Debug Info

void ledTest();
void irSensorDigitalTest();
void irSensorAnalogTest();
void sonarI2CTest();


int main() {
    irSensorDigitalTest();
}

