#pragma once

#include "AbstractComponent.h"
#include "vector"

#define MIN_MSG_SIZE 2 // Length itself (one byte) and checksum (one byte) - minimal possible message
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

    SubMessage* checkForMsgFromPaparazzi(int id);

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

    void readByte();

    /**
     * Process message from Paparazzi, if there is one
     */
    void processPaparazziMsg(int size);

    void nullFunc(int size);

    Serial uart;
    const SubMessage* subMessagesToPaparazzi[MAX_MSG_NUMBER];
    SubMessage subMessagesFromPaparazzi[MAX_MSG_NUMBER];
    uint8_t toPaparazziCount;
    uint8_t fromPaparazziCount;
    uint8_t toPaparazziMsgLength;
    uint8_t toPaparazziMsg[BUF_SIZE];
    uint8_t fromPaparazziMsg[BUF_SIZE];

    uint8_t position;
};