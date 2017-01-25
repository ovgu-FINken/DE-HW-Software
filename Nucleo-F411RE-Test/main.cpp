#include "mbed.h"

DigitalOut  led(LED1);
Serial pc(USBTX, USBRX); //Debug Info

void ledTest();
void irSensorDigitalTest();
void irSensorAnalogTest();
void sonarI2CTest();

/*
 * Main function, put here the things to test
 */
int main() {
    irSensorAnalogTest();
}

void ledTest() {
    while (true) {
        led = !led,
        Thread::wait(500);
    }
}

/*
 * Sharp GP2Y0D805Z0F Digital Distance Sensor 5cm
 * This small digital distance sensor detects objects between 0.5 cm and 5 cm (0.2″ and 2″) away.
 * Documentation: https://www.pololu.com/file/0J284/GP2Y0D805Z0F.pdf
 *
 * Feature summary:
 * Operating voltage: 2.7 V to 6.2 V
 * Average current consumption: 5 mA (typical)
 * Output type: digital signal (low when detecting an object, high otherwise)
 * Steady state update period: 2.56 ms typical (3.77 ms max)
 */
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

/*
 * Pololu Carrier with Sharp GP2Y0A60SZLF Analog Distance Sensor 10-150cm, 5V
 * The GP2Y0A60SZ distance sensor from Sharp offers a wide detection range of 4″ to 60″ (10 cm to 150 cm)
 * and a high update rate of 60 Hz. The distance is indicated by an analog voltage,
 * so only a single analog input is required to interface with the module.
 * The sensor ships installed on our compact carrier board, which makes it easy to integrate this great sensor
 * into your project, and is configured for 5V mode.
 * Documentation: https://www.pololu.com/file/0J812/gp2y0a60szxf_e.pdf
 */
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

/*
 * I2CXL-MaxSonar - EZ Series
 * Documentation: http://www.maxbotix.com/documents/I2CXL-MaxSonar-EZ_Datasheet.pdf
 */
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