#pragma once

#include "AbstractComponent.h"
#include "UARTMessenger.h"

class IRSensorDigital: public AbstractComponent {
public:
    /**
     * @param dataPin
     * @param detectionRange
     */
    IRSensorDigital(UARTMessenger *const uartMsngr, PinName dataPin, float detectionRange);
    bool isInRange();
    virtual void update();

private:
    UARTMessenger *const uartMessenger;
    PinName dataPin;
    AnalogIn sensor;
    float detectionRange;
    bool inRange;
};