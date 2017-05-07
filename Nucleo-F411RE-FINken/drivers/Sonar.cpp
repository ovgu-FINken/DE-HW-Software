#include "Sonar.h"
#include <stdint.h>
#include "IRQLock.h"

    //char cmd[2];
    //while (1) {
//        cmd[0] = 0x01;
//        cmd[1] = 0x00;
//        i2c.write(addr, cmd, 2);
//
//        wait(0.5);
//
//        cmd[0] = 0x00;
//        i2c.write(addr, cmd, 1);
//        i2c.read(addr, cmd, 2);
//
//        float tmp = (float((cmd[0]<<8)|cmd[1]) / 256.0);
//        printf("Temp = %.2f\n", tmp);
//    }
//}

Sonar::Sonar(UARTMessenger *const uartMsngr, uint8_t addr): uartMessenger(uartMsngr), i2c(I2C_SDA, I2C_SCL) {
    id = ++s_id;
    const int address = (0x70 << 1);
    int range;
    char config[2];

}

void Sonar::update() {
    i2c.lock();
    config[0] = 0x51;//initalizing the address as 81
    config[1]=0x00; //set the data register to 0
    i2c.write(address, config, 2);
    timeout.attach(callback(this, &Sonar::read), 0.08); // 80 ms is suggested in documentation
    config[0]=0x00;
    i2c.write(address,config,1);
    i2c.unlock();
}

void Sonar::read() {
    i2c.lock();
    char range_read[2];
    int a = i2c.read(address | 0x01,range_read,2);
    if (a != 0)
        return; // Reading failed
    range = ((range_read[0] << 8)|range_read[1]);
    i2c.unlock();

    subMessage.type = SONAR;
    subMessage.id = id;
    reinterpret_cast<uint16_t*>(subMessage.data)[0] = range;
    subMessage.length = sizeof(range);

    uartMessenger->appendMessage(subMessage);
}

uint16_t Sonar::getRange() {
    return range;
}