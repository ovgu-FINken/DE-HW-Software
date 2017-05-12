#pragma once

#include "AbstractComponent.h"
#include <stdint.h>
#include "UARTMessenger.h"

class Sonar: public AbstractComponent {
public:
    /**
     * Constructor for Sonar
     *
     * @param uartMsngr Pointer to UARTMessenger object, that should be used for sending data to Paparazzi
     * @param addr Address of the Sonar
     */
    Sonar(UARTMessenger *const uartMsngr, uint8_t addr, EventQueue *const queue);
    virtual void update();
    uint16_t getRange();

private:
    void read();

    UARTMessenger *const uartMessenger;
    EventQueue *const queue;
    SubMessage subMessage;
    I2C i2c;
    uint8_t address;
    char config[2];
    uint16_t range;
    Timeout timeout;
};

