#pragma once

#include "AbstractComponent.h"
#include "mbed.h"
#include "PinNames.h"

class IRSensorDigital: public AbstractComponent {
public:
    /**
     *
     * @param dataPin
     * @param detectionRange
     */
    IRSensorDigital(PinName dataPin, float detectionRange);
    bool isInRange();
    virtual void update();

private:
    PinName dataPin;
    AnalogIn sensor;
    float detectionRange;
    bool inRange;
};