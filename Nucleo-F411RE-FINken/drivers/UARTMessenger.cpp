#include "UARTMessenger.h"
#include "IRQLock.h"

UARTMessenger::UARTMessenger(PinName tx, PinName rx) : uart(tx, rx) {
    id = ++s_id;
    count = 0;
    messageLength = 2; // Length itself (one byte) and checksum (one byte) - minimal possible message
}

void UARTMessenger::update() {
    IRQLock lock;

    memset(message, 0, BUF_SIZE);

    message[0] = messageLength;

    // add current submessages
    int pos = 1;
    for (int i = 0; i < count; i++) {
        message[pos] = subMessages[i]->id;
        message[++pos] = subMessages[i]->type;
        message[++pos] = subMessages[i]->length;
        for (int j = 0; j < subMessages[i]->length; j++) {
            message[++pos] = subMessages[i]->data[j];
        }
    }
//    for (int i = 0; i < count; i++) {
//        message.push_back(subMessages[i]->id);
//        message.push_back(subMessages[i]->type);
//        message.push_back(subMessages[i]->length);
//        for (int j = 0; j < subMessages[i]->length; j++) {
//            message.push_back(subMessages[i]->data[j]);
//        }
//    }

    calculateChecksum(message, messageLength);

    // send the message via UART
    //uart.write(message, messageLength, nullptr);

    // check if we have
    //uart.read(papparazziMsg, BUF_SIZE, callback(this, &UARTMessenger::processPapparazziMsg));

    count = 0;
    messageLength = 2;
}

void UARTMessenger::appendMessage(const SubMessage &subMessage) {
    IRQLock lock;
    if (count >= MAX_MSG_NUMBER) {
        return;
    }
    subMessages[count] = &subMessage;
    messageLength += subMessages[count]->length + 3;
    count++;
}

bool UARTMessenger::validateChecksum(uint8_t const *pkt, uint8_t const length) {
    uint8_t pos = 0;
    uint8_t sum = 0;
    while (pos < (length - 1)) {
        sum += *(pkt + pos++);
    }
    sum = 0x0 - sum;

    return (sum == *(pkt + pos));
}

void UARTMessenger::calculateChecksum(uint8_t *pkt, uint8_t const length) {
    uint8_t pos = 0;
    uint8_t sum = 0;
    while (pos < (length - 1)) {
        sum += *(pkt + pos++);
    }
    // put the checksum into the data stream
    *(pkt + pos) = 0x0 - sum;
}

void UARTMessenger::processPaparazziMsg() {
    //TODO: good way to get all components?
}