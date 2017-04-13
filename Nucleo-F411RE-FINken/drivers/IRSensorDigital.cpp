#include "IRSensorDigital.h"

IRSensorDigital::IRSensorDigital(UARTMessenger *const uartMsngr, PinName pin, float detectionRange):uartMessenger(uartMsngr),dataPin(pin),sensor(dataPin) {
    this->detectionRange = detectionRange;
    inRange = false;
};

void IRSensorDigital::update() {
    float value = sensor.read();
    if (value > detectionRange) {
        inRange = false;
    } else {
        inRange = true;
    }

    SubMessage subMessage;
    subMessage.type = IRDIGITAL;
    subMessage.id = id;
    reinterpret_cast<bool*>(subMessage.data)[0] = inRange;
    subMessage.length = sizeof(inRange);

    uartMessenger->appendMessage(subMessage);
}

bool IRSensorDigital::isInRange() {
    return inRange;
}





