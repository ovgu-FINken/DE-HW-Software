#include "IRSensorDigital.h"
#include "mbed.h"
#include "PinNames.h"

IRSensorDigital::IRSensorDigital(PinName pin, float detectionRange):dataPin(pin),sensor(dataPin) {
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





