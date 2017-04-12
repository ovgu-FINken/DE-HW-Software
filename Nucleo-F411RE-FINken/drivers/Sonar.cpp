#include "Sonar.h"
#include <stdint.h>
#include "IRQLock.h"

Sonar::Sonar(UARTMessenger *const uartMsngr, uint8_t addr): uartMessenger(uartMsngr), i2c(I2C_SDA, I2C_SCL) {
    address = addr;
}

void Sonar::update() {
    IRQLock lock;
    config_r[0] = 0x51;
    config_r[1] = 0x00;
    i2c.write(address, config_r, 1);
    timeout.attach(callback(this,&Sonar::read), 0.07);
}

void Sonar::read() {
    IRQLock lock;
    config_r[0] = 0x02;
    if (i2c.read(address | 1, range_read, 2) != 0) //read the two-byte range data
        return; // Reading failed
    else {
        range = ((range_read[0] << 8) + range_read[1]);
    }
}

uint16_t Sonar::getRange() {
    return range;
}