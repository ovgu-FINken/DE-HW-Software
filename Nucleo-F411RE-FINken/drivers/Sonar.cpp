#include "Sonar.h"
#include <stdint.h>
#include "IRQLock.h"
#include "mbed_events.h"

/**
 * Constructor for Sonar
 */
Sonar::Sonar(UARTMessenger *const uartMsngr, uint8_t addr, EventQueue *const queue) : uartMessenger(uartMsngr), queue(queue), i2c(I2C_SDA, I2C_SCL) {
    id = ++s_id;
    i2c.frequency(50000);
    address = addr << 1;
}

/**
 * Write value to i2c for the sonar.
 */
void Sonar::update() {
    i2c.lock();
    config[0] = 0x51; //initializing the address as 81
    int a = i2c.write(address & ~1, config, 1);
    if (a != 0)
        return; // Writing failed
    i2c.unlock();

    // move read function to the queue to be called after 80 ms
    queue->call_in(80, callback(this, &Sonar::read));
}

/**
 * Read the range and then bit will be shifted towards left 8 bytes.
 * Type of the sensor is SONAR, id of the sensor, converting to data range to uint16_t, length of the range.
 * Appends the message to uart list.
 */
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