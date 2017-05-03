#include "LEDStrip.h"
#include "WS2812.h"
#include "PixelArray.h"

LEDStrip::LEDStrip(UARTMessenger *const uartMsngr, PinName pin, int size, int zeroHigh, int zeroLow, int oneHigh, int oneLow): uartMessenger(uartMsngr), ws(pin, size, zeroHigh, zeroLow, oneHigh, oneLow), px(size) {
    id = ++s_id;
    ws.useII(WS2812::OFF); // use per-pixel intensity scaling
    stripSize = size;
    offset = 0;
    mode = 0;
    px.Set(0, 0xFF0000);
}

void LEDStrip::setMode(uint8_t mode) {
    this->mode = mode;
}

void LEDStrip::setColor(int color) {
    px.Set(0, color);
}

void LEDStrip::update() {
    switch (mode) {
        case 0:
            // Control from Paparazzi. Need to send the id of the LEDStrip first to be able to communicate
            subMessage.type = IRANALOG;
            subMessage.id = id;
            subMessage.length = 0;

            uartMessenger->appendMessage(subMessage);
            break;
        case 1:
            // Running red LED
            ws.write_offsets(px.getBuf(), offset, offset, offset);
            offset = (offset + 1) % stripSize;
            break;
    }
}

void LEDStrip::onPaparazziMsg(uint8_t *msg) {
    // TODO: implement reaction on message from paparazzi
    return;
}
