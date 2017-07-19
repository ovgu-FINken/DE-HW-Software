#include "mbed.h"
#include "tests.h"
#include "../drivers/LEDStrip/WS2812.h"
#include "../drivers/LEDStrip/PixelArray.h"
#include <vector>

DigitalOut led(LED1);
Serial pc(USBTX, USBRX); //Debug Info

void ledTest() {
    while (true) {
        led = !led;
        Thread::wait(500);
    }
}

/*
 * Sharp GP2Y0D805Z0F Digital Distance Sensor 5cm
 * This small digital distance sensor detects objects between 0.5 cm and 5 cm (0.2? and 2?) away.
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
        } else led = !led;
        Thread::wait(200);
    }
}

/*
 * Pololu Carrier with Sharp GP2Y0A60SZLF Analog Distance Sensor 10-150cm, 5V
 * The GP2Y0A60SZ distance sensor from Sharp offers a wide detection range of 4? to 60? (10 cm to 150 cm)
 * and a high update rate of 60 Hz. The distance is indicated by an analog voltage,
 * so only a single analog input is required to interface with the module.
 * The sensor ships installed on our compact carrier board, which makes it easy to integrate this great sensor
 * into your project, and is configured for 5V mode.
 * Documentation: https://www.pololu.com/file/0J812/gp2y0a60szxf_e.pdf
 */

std::vector <std::vector<int>> lookupTable = {{800,  1300},
                                              {830,  1000},
                                              {900,  800},
                                              {1150, 600},
                                              {1650, 400},
                                              {2700, 200}};

void irSensorAnalogTest() {
    AnalogIn sensor(A0);

    while (true) {
        float sensorOutput = sensor.read() * 3300;
        float distance = 0;

        // left border of lookup table
        if (sensorOutput <= lookupTable[0][0]) {
            distance = lookupTable[0][1];
        } else if (sensorOutput >= lookupTable[lookupTable.size() - 1][0]) {
            // right border of lookup table
            distance = lookupTable[lookupTable.size() - 1][1];
        } else {
            // inside the table
            int i = 0;
            while (sensorOutput > lookupTable[++i][0]) {
                //iterate until we get to the first value in lookup table, that is bigger then our sensor output
            }
            // w: something in range [0;1], for position in interval between i - 1 and i
            float w = (float) (sensorOutput - lookupTable[i - 1][0]) / (lookupTable[i][0] - lookupTable[i - 1][0]);
            distance = (1 - w) * lookupTable[i - 1][1] + w * lookupTable[i][1];
        }

        pc.printf("%f\t%f\n\r", sensorOutput, distance);

        Thread::wait(200);
    }
}


/*
 * I2CXL-MaxSonar - EZ Series
 * Documentation: http://www.maxbotix.com/documents/I2CXL-MaxSonar-EZ_Datasheet.pdf
 */
void sonarI2CTest() {
    I2C i2c(I2C_SDA, I2C_SCL);
    const int address = (0x70 << 1);
    char config[2];
    char range_read[2];
    int range;
    while (true) {
        config[0] = 0x51; //initializing the address as 81
        int a = i2c.write(address & ~1, config, 1);
        if (a != 0)
            pc.printf("Writing failed");

        Thread::wait(80);

        a = i2c.read(address | 0x01, range_read, 2); //read the two-byte range data
        if (a != 0)
            pc.printf("Reading failed");
        else {
            range = ((range_read[0] << 8) + range_read[1]);
            pc.printf("%i\n\r", range); //print range on screen
        }

        Thread::wait(200);

    }
}

#define WS2812_BUF 24
#define NUM_COLORS 6
#define NUM_LEDS_PER_COLOR 3

/*
 * WS2812 LED
 * Documentation: https://cdn-shop.adafruit.com/datasheets/WS2812.pdf
 */
void LEDStripTest() {
    int unsigned CPU_Frequency = 16; // for microseconds
    PixelArray px(WS2812_BUF);
    WS2812 ws(PC_5, WS2812_BUF, 0, 5, 4, 3);

    ws.useII(WS2812::OFF); // use per-pixel intensity scaling
    int colorbuf[NUM_COLORS] = {0x00FF00, 0x2f2f00, 0x002f00, 0x002f2f, 0x00002f, 0x2f002f};

    px.SetAll(0x0000FF);
    //px.SetAllI(50);

//for (int i = 0; i < WS2812_BUF; i++)
//{
//   px.Set(i, colorbuf[(i / NUM_LEDS_PER_COLOR) % NUM_COLORS]);
//}
//
//for (int j=0; j<WS2812_BUF; j++)
//{
//    // px.SetI(pixel position, II value)
//    px.SetI(j, 0xf+(0xf*(j%NUM_LEDS_PER_COLOR)));
//}

    while (1) {
        for (int i = 0; i < WS2812_BUF; i++) {
            // px.SetI(pixel position, II value)
            //px.SetI(j, 0xf+(0xf*(j%NUM_LEDS_PER_COLOR)));
            px.Set(i, colorbuf[(i / 3) % 6]);
        }
        ws.write(px.getBuf());

        led = !led;
        wait(0.5);

    }

}
