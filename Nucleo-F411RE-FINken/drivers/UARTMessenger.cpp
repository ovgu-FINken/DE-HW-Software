#include "UARTMessenger.h"
#include "IRQLock.h"
#include <string>
#include <vector>

UARTMessenger::UARTMessenger(PinName tx, PinName rx): uart(tx, rx) {
    count = 0;
    startByte = 254;
    stopByte = 255;
    messageLength = 4; // Length itself (two bytes) and checksum (two bytes) - minimal possible message
}

void UARTMessenger::update() {
    IRQLock lock;

    std::vector<uint8_t> message;

    message[0] = messageLength & 0xFF;
    message[1] = messageLength >> 8;

    // reserve place for checksum
    message[3] = 0;
    message[4] = 0;

    // add current submessages
    for (int i = 0; i < count; i++) {
        message.push_back(subMessages[i]->id);
        message.push_back(subMessages[i]->type);
        message.push_back(subMessages[i]->length);
        for (int j = 0; j < subMessages[i]->length; j++) {
            message.push_back(subMessages[i]->data[j]);
        }
    }

    uint16_t checksum = calculateChecksum(message);
    message[3] = checksum & 0xFF;
    message[4] = checksum >> 8;

    // send the message
    for (int i = 0; i < message.size(); i++) {
        uart.putc(message[i]);
    }

    // empty the subMessages array?
    count = 0;
}

void UARTMessenger::appendMessage(const SubMessage& subMessage) {
    IRQLock lock;
    subMessages[count] = &subMessage;
    messageLength += subMessages[count]->length + 3;
    count++;
}

uint16_t UARTMessenger::calculateChecksum(std::vector<uint8_t> message) {
    // TODO: calculate checksum
    return 0;
}