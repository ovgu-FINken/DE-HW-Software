#include "Sonar.h"
#include <stdint.h>
#include "IRQLock.h"
#include "mbed_events.h"

Sonar::Sonar(UARTMessenger *const uartMsngr, uint8_t addr, EventQueue *const queue) : uartMessenger(uartMsngr), queue(queue), i2c(I2C_SDA, I2C_SCL) {
    id = ++s_id;
    i2c.frequency(50000);
    address = addr << 1;

}

void Sonar::update() {
    i2c.lock();
    config[0] = 0x51; //initializing the address as 81
    int a = i2c.write(address & ~1, config, 1);
    if (a != 0)
        return; // Writing failed

    i2c.unlock();

    queue->call_in(80, callback(this, &Sonar::read));
}

void Sonar::read() {
    i2c.lock();
    char range_read[2];
    int a = i2c.read(address | 0x01, range_read, 2); //read the two-byte range data
    if (a != 0)
        return; // Reading failed
    range = ((range_read[0] << 8) | range_read[1]);
    i2c.unlock();

    subMessage.type = SONAR;
    subMessage.id = id;
    reinterpret_cast<uint16_t *>(subMessage.data)[0] = range;
    subMessage.length = sizeof(range);

    uartMessenger->appendMessage(subMessage);
}

uint16_t Sonar::getRange() {
    return range;
}