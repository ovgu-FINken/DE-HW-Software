#include "mbed.h"
#include "tests/tests.h"
#include "drivers/AbstractComponent.h"
#include "drivers/Sonar.h"
#include "drivers/IRSensorAnalog.h"
#include "drivers/IRSensorDigital.h"
#include "drivers/UARTMessenger.h"


// Lookup tables for sensors, pairs {sensorOutput, distance} in acceding order of sensorOutput, distance in millimeters
int** pololu10_150 = {{800, 1300},{830, 1000},{90, 800}};

const int compNumber = 20;

/*
 * Main function
 */
int main() {
    // Initialization of components, connected to the board
    AbstractComponent* components[compNumber];


    while (true) {
        for (int i = 0; i < compNumber; i++) {
            components[i]->update();
        }

    }
}
