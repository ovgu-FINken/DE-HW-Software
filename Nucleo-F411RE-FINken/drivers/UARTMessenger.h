#pragma once

#include "AbstractComponent.h"
#include "vector"

#define MAX_MSG_NUMBER 16
#define BUF_SIZE 256

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

    uint8_t* checkForMsgFromPaparazzi(int id);

private:
    /**
     * Validate the checksum of the byte array
     *
     * @param pkt pointer to the byte array
     * @param length number of bytes in the array
     *
     * @return true if validation was successful
     */
    bool validateChecksum(uint8_t const *pkt, uint8_t const length);

    /**
     * Add checksum to the end of the byte array
     *
     * @param pkt pointer to the byte array
     * @param length number of bytes in the array
     */
    void calculateChecksum(uint8_t *pkt, uint8_t const length);

    /**
     * Process message from Paparazzi, if there is one
     */
    void processPaparazziMsg();

    void nullFunc();

    Serial uart;
    const SubMessage* subMessages[MAX_MSG_NUMBER];
    int count;
    uint8_t messageLength;
    uint8_t message[BUF_SIZE];
    uint8_t paparazziMsg[BUF_SIZE];
};