#pragma once

#include "AbstractComponent.h"
#include "mbed.h"
#include "PinNames.h"

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
    IRSensorAnalog(PinName dataPin, const int* lookupTable[2]);

    /**
     *
     * @return - range of sensor in meters
     */
    float getRange();

    virtual void update();

private:
    float toRange(float sensorOutput);

    PinName dataPin;
    AnalogIn sensor;
    const int** lookupTable;
    float range;
};