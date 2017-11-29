#pragma once

#include "AbstractComponent.h"
#include "vector"

#define MAX_MSG_NUMBER 16
#define BUF_SIZE 256
#define BUF_SIZE_ENCODED 512

class UARTMessenger: public AbstractComponent {
public:
    /**
     * @param tx transmit pin
     * @param rx receive pin
     */
    UARTMessenger(PinName tx, PinName rx);

    virtual void update();

    /**
     * @param subMessage message to be added
     */
    void appendMessage(const SubMessage& subMessage);

    /**
     * @param id - id of the component
     * @return SubMessage* if found, nullptr otherwise
     */
    SubMessage* checkForMsgFromPaparazzi(int id);

private:
    /**
     * @param pkt pointer to the byte array
     * @param length number of bytes in the array
     *
     * @return true if validation was successful
     */
    bool validateChecksum(uint8_t const *pkt, uint8_t const length);

    /**
     * @param pkt pointer to the byte array
     * @param length number of bytes in the array
     */
    void calculateChecksum(uint8_t *pkt, uint8_t const length);

    void encode();

    bool decode(int size);

    /**
     * @param size - size of the message
     */
    void processPaparazziMsg(int size);

    /**
     * @param size - size of the message
     */
    void nullFunc(int size);

    Serial uart;
    const SubMessage* subMessagesToPaparazzi[MAX_MSG_NUMBER];
    SubMessage subMessagesFromPaparazzi[MAX_MSG_NUMBER];

    uint8_t toPaparazziCount;
    uint8_t fromPaparazziCount;
    uint8_t toPaparazziMsgLength;
    uint8_t toPaparazziMsgEncodedLength;
    uint8_t toPaparazziMsg[BUF_SIZE];
    uint8_t fromPaparazziMsg[BUF_SIZE];
    uint8_t toPaparazziMsgEncoded[BUF_SIZE_ENCODED];
    uint8_t fromPaparazziMsgEncoded[BUF_SIZE_ENCODED];

    uint8_t startByte;
    uint8_t stopByte;
    uint8_t escapeByte;
};
