#pragma once

#include "mbed.h"
#include "PinNames.h"
#include "SubMessage.h"

class AbstractComponent {
public:
    /**
     * Main function for using all the components.
     * Update component data and add this information to UARTMessenger.
     */
    virtual void update() = 0;
    /**
     * React to the message from Paparazzi.
     * At the moment only relevant for LED strip
     *
     * @param msg Message from Paprazzi
     */
    void onPaparazziMsg(uint8_t* msg) {
        return;
    };
    void setPriority(int p) {
        priority = p;
    }
    int getPriority() {
        return priority;
    }

protected:
    int priority = 0;
    int id = 0;
};