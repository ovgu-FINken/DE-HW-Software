#include "IRSensorAnalog.h"
#include "mbed.h"
#include "PinNames.h"

IRSensorAnalog::IRSensorAnalog(PinName pin, const int* lookupTable[2]):dataPin(pin),sensor(dataPin) {
    this->lookupTable = lookupTable;
    range = 0;
}

void IRSensorAnalog::update() {
    float value = sensor.read();
    range = toRange(value);
}

float IRSensorAnalog::toRange(float sensorOutput) {
    float distance = 0;

    return distance;
}

float IRSensorAnalog::getRange() {
    return range;
}