#include "IRSensorAnalog.h"
#include "mbed.h"
#include "PinNames.h"
#include <vector>

IRSensorAnalog::IRSensorAnalog(PinName pin, std::vector<std::vector<int> > lookupTable):dataPin(pin),sensor(dataPin) {
    this->lookupTable = lookupTable;
    //this->uartMessenger = uart;
    range = 0;
}

void IRSensorAnalog::update() {
    float value = sensor.read() * 3300; //multiply by current in the system, mV
    range = toRange(value);
}

float IRSensorAnalog::toRange(float sensorOutput) {
    float distance = 0;

    // left border of lookup table
    if (sensorOutput <= lookupTable[0][0]) {
        distance = lookupTable[0][1];
        return distance;
    }

    // right border of lookup table
    if (sensorOutput >= lookupTable[lookupTable.size()-1][0]) {
        distance = lookupTable[lookupTable.size()-1][1];
        return distance;
    }

    // inside the table
    int i=0;
    while (sensorOutput > lookupTable[++i][0]) {
        //iterate until we get to the first value in lookup table, that is bigger then our sensor output
    }
    // w: something in range [0;1], for position in interval between i - 1 and i
    float w = (float) (sensorOutput - lookupTable[i-1][0]) / (lookupTable[i][0] - lookupTable[i-1][0]);
    distance = (1 - w) * lookupTable[i-1][1] + w * lookupTable[i][1];

    return distance;
}

float IRSensorAnalog::getRange() {
    return range;
}