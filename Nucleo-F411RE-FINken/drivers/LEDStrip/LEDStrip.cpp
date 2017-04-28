#include "LEDStrip.h"
#include "WS2812.h"
#include "PixelArray.h"

LEDStrip::LEDStrip(PinName pin, int size, int zeroHigh, int zeroLow, int oneHigh, int oneLow): ws(pin, size, zeroHigh, zeroLow, oneHigh, oneLow), px(size) {
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

void LEDStrip::update() {
    switch (mode) {
        case 0:
            // Control from Paparazzi
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
