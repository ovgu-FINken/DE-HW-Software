#include "LEDStrip.h"
#include "WS2812.h"
#include "PixelArray.h"

LEDStrip::LEDStrip(UARTMessenger *const uartMsngr, PinName pin, int size, int zeroHigh, int zeroLow, int oneHigh, int oneLow): uartMessenger(uartMsngr), ws(pin, size, zeroHigh, zeroLow, oneHigh, oneLow), px(size) {
    id = ++s_id;
    ws.useII(WS2812::OFF); // use per-pixel intensity scaling
    stripSize = size;
    offset = 0;
    mode = 0;
}

void LEDStrip::setMode(uint8_t mode) {
    this->mode = mode;
}

void LEDStrip::setColor(unsigned int color) {
    px.Set(0, color);
}

void LEDStrip::update() {
    switch (mode) {
        case 0: {
            // Control from Paparazzi

            SubMessage *paparazziMsg = uartMessenger->checkForMsgFromPaparazzi(id);
            if (paparazziMsg != nullptr) {
                onPaparazziMsg(paparazziMsg);
                ws.write_offsets(px.getBuf(), 0, 0, 0);
            }

            //  Need to send the id of the LEDStrip first to be able to communicate. Do this every time?
            subMessage.type = LEDSTRIP;
            subMessage.id = id;
            subMessage.length = 0;

            uartMessenger->appendMessage(subMessage);
        }
            break;
        case 1:
            // Running red LED
            ws.write_offsets(px.getBuf(), offset, offset, offset);
            offset = (offset + 1) % stripSize;
            break;
        default:
            break;
    }
}

void LEDStrip::onPaparazziMsg(SubMessage* msg) {
    int pos = 0;
    for (int i = 0; i < msg->length / 4; i++) {
        uint8_t led = msg->data[pos];
        px.SetR(led, msg->data[++pos]);
        px.SetG(led, msg->data[++pos]);
        px.SetB(led, msg->data[++pos]);
    }
    return;
}
