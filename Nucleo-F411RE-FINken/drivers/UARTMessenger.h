#pragma once

#include "AbstractComponent.h"
#include "vector"

class UARTMessenger: public AbstractComponent {
public:
    /**
     * Constructor for UARTMessenger
     *
     * @param tx transmit pin
     * @param rx receive pin
     */
    UARTMessenger(PinName tx, PinName rx);
    virtual void update();

    /**
     * Append new message for sending to Paparazzi
     *
     * @param subMessage message to be added
     */
    void appendMessage(const SubMessage& subMessage);
    uint16_t calculateChecksum(std::vector<uint8_t> message);

private:
    Serial uart;
    const SubMessage* subMessages[16];
    int count;
    uint8_t startByte;
    uint8_t stopByte;
    uint16_t messageLength;
};