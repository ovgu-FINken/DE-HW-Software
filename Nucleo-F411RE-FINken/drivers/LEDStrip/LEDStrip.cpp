//#include "LEDStrip.h"
//#include "WS8212.h"
//#include "PixelArray.h"
//
//LEDStrip::LEDStrip(PinName pin, int size, int zeroHigh, int zeroLow, int oneHigh, int oneLow): ws(pin, size, zeroHigh, zeroLow, oneHigh, oneLow), px(size) {
//
//    ws.useII(WS2812::PER_PIXEL); // use per-pixel intensity scaling
//    stripSize = size;
//    int r_offset = 0;
//    int g_offset = 0;
//    int b_offset = 0;
//
//    /*
//    // set up the colours we want to draw with
//    int colorbuf[NUM_COLORS] = {0x2f0000,0x2f2f00,0x002f00,0x002f2f,0x00002f,0x2f002f};
//
//    // for each of the colours (j) write out 10 of them
//    // the pixels are written at the colour*10, plus the colour position
//    // all modulus 60 so it wraps around
//    for (int i = 0; i < WS2812_BUF; i++) {
//        px.Set(i, colorbuf[(i / NUM_LEDS_PER_COLOR) % NUM_COLORS]);
//    }
//
//    // now all the colours are computed, add a fade effect using intensity scaling
//    // compute and write the II value for each pixel
//    for (int j=0; j<WS2812_BUF; j++) {
//        // px.SetI(pixel position, II value)
//        px.SetI(j, 0xf+(0xf*(j%NUM_LEDS_PER_COLOR)));
//    }
//    */
//
//}
//
//void LEDStrip::update() {
//    ws.write(px.getBuf());
//}
