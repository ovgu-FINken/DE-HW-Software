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
    subMessage.data = reinterpret_cast<uint8_t*>(&inRange);
    subMessage.length = sizeof(subMessage.data);

    uartMessenger->appendMessage(subMessage);
}

bool IRSensorDigital::isInRange() {
    return inRange;
}





