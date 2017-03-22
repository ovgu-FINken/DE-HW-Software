#pragma once

#include "AbstractComponent.h"
#include "mbed.h"

class UARTMessenger: public AbstractComponent {
public:
    enum infoType {
        Sonar,
        IRSensorAnalog,
        IRSensorDigital
    };
    struct SubMessage {
        infoType type;
        uint8_t id;
        uint8_t length;
        uint8_t data[16];
    };
    UARTMessenger(PinName tx, PinName rx);
    virtual void update();
    void appendMessage(const SubMessage& subMessage);

private:
    Serial uart;
    SubMessage* subMessages[16];
    int count;
    uint8_t startByte;
    uint8_t stopByte;
};