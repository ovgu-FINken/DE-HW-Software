#include "IRSensorAnalog.h"
#include <vector>

#define REFERENCE_VOLTAGE 3300 // in mV

/**
 * Constructor for analog IRSensor
 */
IRSensorAnalog::IRSensorAnalog(UARTMessenger *const uartMsngr, PinName pin, std::vector<std::vector<int> > lookupTable): uartMessenger(uartMsngr), dataPin(pin), sensor(dataPin) {
    id = ++s_id;
    this->lookupTable = lookupTable;
    range = 0;
}

/**
 * Read the sensor value and product with the reference voltage.
 * We can get range from toRange() function.
 * Submessage is struct where we get type of the sensor = IRANALOG, id of the sensor, data, length of the range size.
 * UartMessenger appends submessage which is in UARTMessenger.
 */
void IRSensorAnalog::update() {
    float value = sensor.read() * REFERENCE_VOLTAGE;
    range = toRange(value);

    subMessage.type = IRANALOG;
    subMessage.id = id;
    reinterpret_cast<float*>(subMessage.data)[0] = range;
    subMessage.length = sizeof(range);

    uartMessenger->appendMessage(subMessage);
}

/**
 * Calculates distance from voltage output and lookup table.
 *
 * @param sensorOutput output of the sensor - voltage
 * @return float value of a range between min and max values from lookup table
 */
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