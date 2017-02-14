#pragma once

#include "AbstractComponent.h"
#include <stdint.h>
#include "mbed.h"

class Sonar: public AbstractComponent {
public:
    Sonar(uint8_t addr);
    virtual void update();
    uint16_t getRange();

private:
    I2C i2c;
    uint8_t address;
    char config_r[2];
    char range_read[2];
    uint16_t range;
    Timeout timeout;
    bool waiting = false;

    void read();
};

