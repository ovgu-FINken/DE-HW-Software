#include "mbed.h"
#include "PinNames.h"
#include "tests/tests.h"
#include "drivers/AbstractComponent.h"
#include "drivers/Sonar.h"
#include "drivers/IRSensorAnalog.h"
#include "drivers/IRSensorDigital.h"
#include "drivers/UARTMessenger.h"
#include "drivers/LEDStrip/LEDStrip.h"


// Lookup tables for sensors, pairs {sensorOutput, distance} in acceding order of sensorOutput, distance in millimeters
std::vector<std::vector<int> > pololu10_150 = {{800, 1300},{830, 1000},{900, 800},{1150, 600},{1650, 400},{2700, 200}};

#define COMP_NUMBER 20

/*
 * Main function
 */
int main() {
    // If you want to rum one of the tests from tests.cpp, just call it here

    // Initialization of components, connected to the board
    // First two parameters for all driver's constructors: uartMessenger
    // Priority of all components by default - 0, can be changed manually. Priority = order of update, lower first
    AbstractComponent* components[COMP_NUMBER];

    UARTMessenger *uartMessenger = new UARTMessenger(USBTX, USBRX); // set pins
    uartMessenger->setPriority(5);

    components[0] = uartMessenger;
    components[1] = new IRSensorAnalog(uartMessenger, A0, pololu10_150);
    components[2] = new Sonar(uartMessenger, 0x70 << 1);
    components[3] = new LEDStrip(PC_5, 24, 0, 5, 4, 3); // experimental values
    //dynamic_cast<LEDStrip*>(components[3])->setMode(1); // TODO ask if there is better way

    // sort all components according to their priority
    int size = sizeof(components);
    for (int sorted = 0, maxIndex = 0; sorted < size; sorted++) {
        for (int i = 0, max = 0; i < size - sorted; i++) {
            if (components[i]->getPriority() > max) {
                max = components[i]->getPriority();
                maxIndex = i;
            }
        }
        AbstractComponent *buf = components[size - sorted];
        components[size - sorted] = components[maxIndex];
        components[maxIndex] = buf;
    }

    while (true) {
        for (int i = 0; i < COMP_NUMBER; i++) {
            components[i]->update();
        }

    }
}