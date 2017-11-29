#include <cstring>
#include "UARTMessenger.h"
#include "IRQLock.h"

/**
 * Constructor for UARTMessenger
 */
UARTMessenger::UARTMessenger(PinName tx, PinName rx) : uart(tx, rx, 9600) {
    id = ++s_id;

    toPaparazziCount = 0;
    fromPaparazziCount = 0;
    toPaparazziMsgLength = MIN_MSG_SIZE;

    stopByte = 0xFE;
    startByte = 0xFD;
    escapeByte = 0xFC;
}

void UARTMessenger::update() {
    IRQLock lock;

    toPaparazziMsg[0] = toPaparazziCount;

    // add current submessages
    int pos = 0;
    for (int i = 0; i < toPaparazziCount; i++) {
        toPaparazziMsg[++pos] = subMessagesToPaparazzi[i]->id;
        toPaparazziMsg[++pos] = subMessagesToPaparazzi[i]->type;
        toPaparazziMsg[++pos] = subMessagesToPaparazzi[i]->length;
        for (int j = 0; j < subMessagesToPaparazzi[i]->length; j++) {
            toPaparazziMsg[++pos] = subMessagesToPaparazzi[i]->data[j];
        }
    }

    calculateChecksum(toPaparazziMsg, toPaparazziMsgLength);
    toPaparazziMsgLength++;

    // add start, stop and escape bytes to the toPaparazziMsg and save it to toPapparazziMsgEncoded variable
    encode();

    // send the message via UART
    uart.write(toPaparazziMsgEncoded, toPaparazziMsgEncodedLength, callback(this, &UARTMessenger::nullFunc));

    // forget old messages from Paparazzi
    memset(toPaparazziMsgEncoded, 0, BUF_SIZE_ENCODED);
    memset(toPaparazziMsg, 0, BUF_SIZE)

    // check if we have message from Paparazzi
    uart.read(fromPaparazziMsgEncoded, BUF_SIZE_ENCODED, callback(this, &UARTMessenger::processPaparazziMsg), SERIAL_EVENT_RX_COMPLETE | SERIAL_EVENT_RX_CHARACTER_MATCH, stopByte);

    // forget about old messages to Paparazzi
    toPaparazziCount = 0;
    toPaparazziMsgLength = 1; // there is always one byte for number of sub messages
}

void UARTMessenger::encode() {
    toPaparazziMsgEncodedLength = toPaparazziMsgLength;

    uint8_t pos = -1;
    // start byte in the beginning
    toPaparazziMsgEncoded[++pos] = startByte;
    
    for (int i = 0; i < toPaparazziMsgLength; i++) {
        if (toPaparazziMsg[i] == startByte || toPaparazziMsg[i] == stopByte || toPaparazziMsg[i] == escateByte) {
            // escape this character - put escape byte before and convert the problematic byte
            toPaparazziMsgEncoded[++pos] = escapeByte;
            // use XOR between escape byte and problematic byte for conversion
            toPaparazziMsgEncoded[++pos] = escapeByte ^ toPaparazziMsg[i];

            toPaparazziMsgEncodedLength++;
        } else {
            toPaparazziMsgEncoded[++pos] = toPaparazziMsg[i];
        }
    }

    // stop byte in the end
    toPaparazziMsgEncoded[++pos] = stopByte;
}

bool UARTMessenger::decode(int size) {
    uint8_t pos = -1;

    if (fromPaparazziMsgEncoded[0] != startByte || fromPaparazziMsgEncoded[size - 1] != stopByte) {
        // start or stop byte is not found in the right place
        return false;
    }

    for (int i = 1; i < size - 1; i++) {
        if (fromPaparazziMsgEncoded[i] == escateByte) {
            // next character is escaped, we need to convert it back
            fromPaparazziMsg[++pos] = escapeByte ^ fromPaparazziMsgEncoded[++i];
        } else {
            fromPaparazziMsg[++pos] = fromPaparazziMsgEncoded[i];
        }
    }

    return true;
}

/**
 * Append new message for sending to Paparazzi.
 */
void UARTMessenger::appendMessage(const SubMessage &subMessage) {
    IRQLock lock;
    if (toPaparazziCount >= MAX_MSG_NUMBER) {
        return;
    }
    subMessagesToPaparazzi[toPaparazziCount] = &subMessage;
    toPaparazziMsgLength += subMessagesToPaparazzi[toPaparazziCount]->length + 3;
    toPaparazziCount++;
}

/**
 * Validate the checksum of the byte array
 */
bool UARTMessenger::validateChecksum(uint8_t const *pkt, uint8_t const length) {
    uint8_t pos = 0;
    uint8_t sum = 0;
    while (pos < (length - 1)) {
        sum += *(pkt + pos++);
    }
    sum = 0x0 - sum;

    return (sum == *(pkt + pos));
}

/**
 * Add checksum to the end of the byte array
 */
void UARTMessenger::calculateChecksum(uint8_t *pkt, uint8_t const length) {
    uint8_t pos = 0;
    uint8_t sum = 0;
    while (pos < (length - 1)) {
        sum += *(pkt + pos++);
    }
    // put the checksum into the data stream
    *(pkt + pos) = 0x0 - sum;
}

/**
 * Process message from Paparazzi, if there is one.
 * Used as callback for mbed read() function.
 */
void UARTMessenger::processPaparazziMsg(int size) {

    // decode the message to get rid of start, stop and escape bytes, saving result to fromPaparazziMsg variable,
    // also check if checksum is correct
    if (decode(size) && validateChecksum(fromPaparazziMsg, size)) {

        // Currently it's just overwriting the old messages
        fromPaparazziCount = fromPaparazziMsg[0];

        int pos = 1;
        for(int i = 0; i < fromPaparazziCount && i < MAX_MSG_NUMBER; i++) {
            SubMessage paparazziSubMessage;

            paparazziSubMessage.type = fromPaparazziMsg[pos++];
            paparazziSubMessage.id = fromPaparazziMsg[pos++];
            paparazziSubMessage.length = fromPaparazziMsg[pos++];

            for (int j = 0; j < paparazziSubMessage.length; j++) {
                paparazziSubMessage.data[j] = fromPaparazziMsg[pos++];
            }

            subMessagesFromPaparazzi[i] = paparazziSubMessage;
        }
    }
}

/**
 * Used as null callback for mbed write() function
 */
void UARTMessenger::nullFunc(int size) {}

/**
 * check if message from paparazzi has something for component with this id
 */
SubMessage* UARTMessenger::checkForMsgFromPaparazzi(int id) {
    // check if message from paparazzi has something for component with this id
    for (int i = 0; i < fromPaparazziCount; i++) {
        if (subMessagesFromPaparazzi[i].id == id) {
            subMessagesFromPaparazzi[i].id = 0; // invalidate this submessage
            return &subMessagesFromPaparazzi[i];
        }
    }
    return nullptr;
}
