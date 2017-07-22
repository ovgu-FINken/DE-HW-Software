#include "IRSensorDigital.h"

IRSensorDigital::IRSensorDigital(UARTMessenger *const uartMsngr, PinName pin, float detectionRange):uartMessenger(uartMsngr),dataPin(pin),sensor(dataPin) {
    id = ++s_id;
    this->detectionRange = detectionRange;
    inRange = false;
};

/**
 * If the value is less than the detectionRange then it will return the true value.
 * SubMessage type is IRDIGITAL, Id of the sensor.
 * reinterpret_cast is that  submessage.data will be converted into boolean.
 * Length is size of inRange.
 * Appends the message to uart list.
 */
void IRSensorDigital::update() {
    float value = sensor.read();
    if (value > detectionRange) {
        inRange = false;
    } else {
        inRange = true;
    }

    subMessage.type = IRDIGITAL;
    subMessage.id = id;
    reinterpret_cast<bool*>(subMessage.data)[0] = inRange;
    subMessage.length = sizeof(inRange);

    uartMessenger->appendMessage(subMessage);
}

bool IRSensorDigital::isInRange() {
    return inRange;
}





