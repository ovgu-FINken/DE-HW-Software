#include "Sonar.h"
#include <stdint.h>
#include "mbed.h"

Sonar::Sonar(uint8_t addr) {
    address = addr;
}

void Sonar::update() {
    config_r[0] = 0x51;
    config_r[1] = 0x00;
    int a = i2c.write(addr, config_r, 1);
    waiting = true;
    timeout.attach(&read, );
}

void read() {
    config_r[0] = 0x02;
    if (i2c.read(addr | 1, range_read, 2) != 0) //read the two-byte range data
        return; // Reading failed
    else {
        range = ((range_read[0] << 8) + range_read[1]);
    }
}

uint8_t Sonar::getRange() {
    return range;
}