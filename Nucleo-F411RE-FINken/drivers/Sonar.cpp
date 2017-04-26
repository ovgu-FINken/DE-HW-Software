#include "Sonar.h"
#include <stdint.h>
#include "IRQLock.h"

Sonar::Sonar(UARTMessenger *const uartMsngr, uint8_t addr): uartMessenger(uartMsngr), i2c(I2C_SDA, I2C_SCL) {
    id = ++s_id;
    address = addr;
    range = 0;

    config_r[0] = 81; // Take a range reading
    config_r[1] = 0;
}

void Sonar::update() {
    //i2c.lock();
    int a = i2c.write(address, config_r, 1);
    if (a != 0)
        return; //Writing failed
    timeout.attach(callback(this, &Sonar::read), 0.08);
    //i2c.unlock();
}

void Sonar::read() {
    //i2c.lock();
    char range_read[2];
    int a = i2c.read((address << 1), range_read, 2); //read the two-byte range data
    if (a != 0)
        return; // Reading failed
    range = ((range_read[0] << 8) + range_read[1]);
    //i2c.unlock();

    subMessage.type = SONAR;
    subMessage.id = id;
    reinterpret_cast<uint16_t*>(subMessage.data)[0] = range;
    subMessage.length = sizeof(range);

    uartMessenger->appendMessage(subMessage);
}

uint16_t Sonar::getRange() {
    return range;
}