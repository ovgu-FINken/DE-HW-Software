#include "LEDStrip.h"
#include "WS2812.h"
#include "PixelArray.h"

/**
 * Constructor for creating a new LED Strip.
 */
LEDStrip::LEDStrip(UARTMessenger *const uartMsngr, PinName pin, int size, int zeroHigh, int zeroLow, int oneHigh,
                   int oneLow) : uartMessenger(uartMsngr), ws(pin, size, zeroHigh, zeroLow, oneHigh, oneLow), px(size) {
    id = ++s_id;
    ws.useII(WS2812::OFF); // off intensity scaling
    stripSize = size;
    offset = 0;
    mode = 0;
}

/**
 * Set LED Strip to manual control instead of getting control action from paparazzi, which is set by default.
 */
void LEDStrip::setMode(uint8_t mode) {
    this->mode = mode;
}

/**
 * Set color to LED Strip.
 */
void LEDStrip::setColor(unsigned int color) {
    px.Set(0, color);
}

/**
 * Set color to only one LED
 */
void LEDStrip::setColor(unsigned int color, uint8_t led) {
    px.Set(led, color);
}

/**
 * The update function will be to the LEDstrip when the control from paparazzi is received and check the message from paparrazi with respect to id.
 * Then check if the paparazzi message received is not null then go to the method onPaparazziMsg to recieve paparazzi message.
 * set write offset passing parameters.
 * while giving the the submessage provide the LED strip Id and append message to the uart messenger
 */
void LEDStrip::update() {
    switch (mode) {
        case 0: {
            // Control from Paparazzi

            SubMessage *paparazziMsg = uartMessenger->checkForMsgFromPaparazzi(id);
            if (paparazziMsg != nullptr) {
                onPaparazziMsg(paparazziMsg);
                ws.write_offsets(px.getBuf(), 0, 0, 0);
            }

            //  Need to send the id of the LEDStrip first to be able to communicate.
            subMessage.type = LEDSTRIP;
            subMessage.id = id;
            subMessage.length = 0;

            uartMessenger->appendMessage(subMessage);
        }
            break;
        case 1: {
            // All colors are set manually in advance

            ws.write_offsets(px.getBuf(), 0, 0, 0);
        }
        case 2: {
            // Running red LED

            ws.write_offsets(px.getBuf(), offset, offset, offset);
            offset = (offset + 1) % stripSize;
            break;
        }
        default:
            break;
    }
}

/**
 * Reaction on the message from Paparazzi.
 * Expected message structure: type (1 byte), id (1 byte), length (1 byte), data (length byte)
 * Datastructure: led id (1 byte), red channel (1 byte), green channel (1 byte), blue channel (1 byte)
 * SubMessage came from Paparazzi
*/
void LEDStrip::onPaparazziMsg(SubMessage *msg) {
    int pos = -1;
    for (int i = 0; i < msg->length / 4; i++) {
        uint8_t led = msg->data[++pos];
        if (msg->length == 4 && led > stripSize) {
            px.SetAllR(msg->data[++pos]);
            px.SetAllG(msg->data[++pos]);
            px.SetAllB(msg->data[++pos]);
        } else {
            px.SetR(led, msg->data[++pos]);
            px.SetG(led, msg->data[++pos]);
            px.SetB(led, msg->data[++pos]);
        }
    }
    return;
}
