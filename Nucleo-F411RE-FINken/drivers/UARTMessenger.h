#pragma once

#include "AbstractComponent.h"
#include "mbed.h"

class UARTMessenger: public AbstractComponent {
public:
    struct SubMessage {
        /**
         * type of the message:
         * 0 - Sonar
         * 1 - IR Sensor analog
         * 2 - IR Sensor digital
         */
        uint8_t type;
        uint8_t id;
        uint8_t length;
        uint8_t data[16];
    };
    UARTMessenger(PinName tx, PinName rx);
    virtual void update();
    void appendMessage(const SubMessage& subMessage);
    uint8_t calculateChecksum();

private:
    Serial uart;
    const SubMessage* subMessages[16];
    int count;
    uint8_t startByte;
    uint8_t stopByte;
    uint16_t messageLength;
};