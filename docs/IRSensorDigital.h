#pragma once

#include "AbstractComponent.h"
#include "UARTMessenger.h"

class IRSensorDigital: public AbstractComponent {
public:
    /**
     * @param dataPin - pin on board, where data pin of IR sensor is connected
     * @param detectionRange - distance of detection for this sensor
     */
    IRSensorDigital(UARTMessenger *const uartMsngr, PinName dataPin, float detectionRange);

    /**
     *
     * @return true if sensor is in range
     */
    bool isInRange();

    virtual void update();

private:
    UARTMessenger *const uartMessenger;
    SubMessage subMessage;
    PinName dataPin;
    AnalogIn sensor;
    float detectionRange;
    bool inRange;
};