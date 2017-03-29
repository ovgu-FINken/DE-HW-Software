#include "mbed.h"
#include "tests/tests.h"
#include "drivers/AbstractComponent.h"
#include "drivers/Sonar.h"
#include "drivers/IRSensorAnalog.h"
#include "drivers/IRSensorDigital.h"
#include "drivers/UARTMessenger.h"
#include "drivers/LEDStrip/LEDStrip.h"


// Lookup tables for sensors, pairs {sensorOutput, distance} in acceding order of sensorOutput, distance in millimeters
std::vector<std::vector<int>> pololu10_150 = {{800, 1300},{830, 1000},{900, 800},{1150, 600},{1650, 400},{2700, 200}};

const int compNumber = 20;

/*
 * Main function
 */
int main() {
    // Initialization of components, connected to the board
    AbstractComponent* components[compNumber];

    UARTMessenger uartMessenger = new UARTMessenger(); // set pins


    components[0] = new IRSensorAnalog(A0, pololu10_150);
    components[1] = new LEDStrip(PC5, 150, 10, 15, 20, 25); // calculate values

    while (true) {
        for (int i = 0; i < compNumber; i++) {
            components[i]->update();
        }

    }
}
