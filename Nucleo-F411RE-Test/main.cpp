#include "mbed.h"

DigitalOut  led(LED1);
Serial pc(USBTX, USBRX); //Debug Info

void ledTest();
void irSensorDigitalTest();
void irSensorAnalogTest();
void sonarI2CTest();


int main() {
    irSensorAnalogTest();
}

void ledTest() {
    while (true) {
        led = !led,
        Thread::wait(500);
    }
}

void irSensorDigitalTest() {
    AnalogIn sensor(A0);   //0.2-5cm

    while (true) {
        pc.printf("Sensor says %f\n\r", sensor.read());
        if (sensor.read() > 0.7) {
            led = 0;
        }
        else led = !led;
        Thread::wait(200);
    }
}

void irSensorAnalogTest() {
    AnalogIn sensor(A1);

    while (true) {
        float val = sensor.read();
        float x = (val - 0.12f) / (0.72f - 0.12f);
        float dist = 10 + (150 - 10) * (100 - x) / 100;
        pc.printf("Sensor: %f; Distance: %f\r\n", val, dist);
        led = !led;
        Thread::wait(100+val*400);
    }
}

void sonarI2CTest() {
    I2C i2c(I2C_SDA, I2C_SCL);
    //I2C rangefinder(pb7, pb8); //sda, sc1
    const int addr = (0x70 << 1);
    char config_r[2];
    char range_read[2];
    int range;
    while (true)
    {
        config_r[0] = 0x51; //set pointer reg to ‘cmd register'
        config_r[1] = 0x00; // config data byte1
        int a = i2c.write(addr, config_r, 1);
        pc.printf("Write returned %i\n\r", a);
        wait(0.07);
        config_r[0] = 0x02; //set pointer reg to 'data register'
        //i2c.write(addr, config_r, 1); //send to pointer 'read range'
        if (i2c.read(addr | 1, range_read, 2) != 0) //read the two-byte range data
            pc.printf("Failed");
        range = ((range_read[0] << 8) + range_read[1]);
        pc.printf("Range = %i cm\n\r", range_read[1]); //print range on screen
        wait(0.05);

    }
}