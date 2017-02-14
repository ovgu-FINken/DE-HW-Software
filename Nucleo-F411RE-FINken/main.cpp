#include "mbed.h"
#include "tests/tests.h"
#include "drivers/AbstractComponent.h"
#include "drivers/Sonar.h"
#include "drivers/IRSensorAnalog.h"
#include "drivers/IRSensorDigital.h"
#include "drivers/UARTMessenger.h"


// Lookup tables for sensors, pairs {sensorOutput, distance} in acceding order of sensorOutput
float** pololu10_150 = {{},{}};

/*
 * Main function
 */
int main() {
    // Initialization of components, connected to the board
    AbstractComponent* components[20];

    while (true) {

    }
}
