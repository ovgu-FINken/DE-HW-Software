#include "UARTMessenger.h"
#include "mbed.h"
#include "IRQLock.h"
#include <string>

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
    uint16_t checksum;
    message[3] = checksum & 0xFF;
    message[4] = checksum >> 8;

    // add current submessages
    for (int i = 0; i < count; i++) {
       message.push_back();
    }

}

void UARTMessenger::appendMessage(const SubMessage &subMessage) {
    IRQLock lock;
    subMessages[count] = subMessage;
    messageLength += subMessages[i]->length + 3;
    count++;
}

uint8_t UARTMessenger::calculateChecksum() {

}