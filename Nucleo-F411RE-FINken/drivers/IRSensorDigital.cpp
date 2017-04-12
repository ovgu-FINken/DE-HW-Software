#include "IRSensorDigital.h"

IRSensorDigital::IRSensorDigital(UARTMessenger *const uartMsngr, PinName pin, float detectionRange):uartMessenger(uartMsngr),dataPin(pin),sensor(dataPin) {
    this->detectionRange = detectionRange;
    inRange = false;
};

void IRSensorDigital::update() {
    float value = sensor.read();
    if (value > detectionRange) {
        inRange = false;
    } else {
        inRange = true;
    }
}

bool IRSensorDigital::isInRange() {
    return inRange;
}





