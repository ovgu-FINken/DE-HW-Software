#include "UARTMessenger.h"
#include "mbed.h"
#include "IRQLock.h"

UARTMessenger::UARTMessenger(PinName tx, PinName rx): uart(tx, rx) {
    count = 0;
    startByte = 255;
    stopByte = 256;
}

void UARTMessenger::update() {
    IRQLock lock = new IRQLock();

    String message;
    uint8_t messageLength = 0;

    for (int i = 0; i < count; i++) {
        messageLength += subMessages[i] + 3;
    }

}

void UARTMessenger::appendMessage(const SubMessage &subMessage) {
    IRQLock lock = new IRQLock();
    subMessages[count] = subMessage;
    count++;
}