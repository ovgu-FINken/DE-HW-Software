#include "IRSensorAnalog.h"
#include <vector>

IRSensorAnalog::IRSensorAnalog(UARTMessenger *const uartMsngr, PinName pin, std::vector<std::vector<int> > lookupTable): uartMessenger(uartMsngr), dataPin(pin), sensor(dataPin) {
    id = ++s_id;
    this->lookupTable = lookupTable;
    range = 0;
}

void IRSensorAnalog::update() {
    float value = sensor.read() * 3300; // TODO: ask about this - multiply by current in the system, mV
    range = toRange(value);

    subMessage.type = IRANALOG;
    subMessage.id = id;
    reinterpret_cast<float*>(subMessage.data)[0] = range;
    subMessage.length = sizeof(range);

    uartMessenger->appendMessage(subMessage);
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