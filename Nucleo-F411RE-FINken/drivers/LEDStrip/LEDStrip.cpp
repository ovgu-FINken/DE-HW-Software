#include "LEDStrip.h"
#include "WS2812.h"
#include "PixelArray.h"

LEDStrip::LEDStrip(PinName pin, int size, int zeroHigh, int zeroLow, int oneHigh, int oneLow): ws(pin, size, zeroHigh, zeroLow, oneHigh, oneLow), px(size) {

    ws.useII(WS2812::GLOBAL); // use per-pixel intensity scaling
    stripSize = size;
    r_offset = 0;
    g_offset = 0;
    b_offset = 0;
    mode = 0;

}

void LEDStrip::update() {
    switch (mode) {
        case 0:
            // Control from Paparazzi
            break;
        case 1:
            // Running red LED
            px.Set(0, 0xFF0000);
            ws.write_offsets(px.getBuf(), r_offset, g_offset, b_offset);
            r_offset += 1 % stripSize;
            g_offset += 1 % stripSize;
            b_offset += 1 % stripSize;
            break;
    }
}
