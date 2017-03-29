#pragma once

#include "AbstractComponent.h"
#include "mbed.h"
#include "PinNames.h"
#include <vector>

class UARTMessenger;
/**
 *
 */
class IRSensorAnalog: public AbstractComponent {
public:
    /**
     * Constructor for analog IRSensor
     *
     * @param dataPin - pin on board, where data pin of IR sensor is connected
     * @param lookupTable - two-dimensional array, describing relation between sensor output and distance, set in millimeters
     */
    IRSensorAnalog(UARTMessenger* uartMessenger, PinName dataPin, std::vector<std::vector<int> > lookupTable);

    /**
     *
     * @return - range of sensor in meters
     */
    float getRange();

    virtual void update();

private:
    float toRange(float sensorOutput);

    UARTMessenger *const uartMessenger;
    PinName dataPin;
    AnalogIn sensor;
    std::vector<std::vector<int> > lookupTable;
    float range;
};