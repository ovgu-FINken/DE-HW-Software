#include "mbed.h"
#include "PinNames.h"
#include "tests/tests.h"
#include "drivers/AbstractComponent.h"
#include "drivers/Sonar.h"
#include "drivers/IRSensorAnalog.h"
#include "drivers/IRSensorDigital.h"
#include "drivers/UARTMessenger.h"
#include "drivers/LEDStrip/LEDStrip.h"
#include "drivers/SimpleLED.h"

#include <memory>
#include <vector>

// Lookup tables for sensors, pairs {sensorOutput, distance} in acceding order of sensorOutput, distance in millimeters
std::vector<std::vector<int> > pololu10_150 = {{800, 1300},{830, 1000},{900, 800},{1150, 600},{1650, 400},{2700, 200}};

/*
 * Main function
 */
int main() {
    // If you want to rum one of the tests from tests.cpp, just call it here

    // Initialization of components, connected to the board
    // First parameter for all driver's constructors: uartMessenger
    // Priority of all components by default - 0, can be changed manually. Priority = order of update, lower first
    using AbstractComponentPtr = unique_ptr<AbstractComponent>;
    using Storage = vector<AbstractComponentPtr>;
    Storage components;

    UARTMessenger *uartMessenger = new UARTMessenger(USBTX, USBRX);
    uartMessenger->setPriority(5);


    //components[0] = uartMessenger;
    //components[0] = new IRSensorAnalog(uartMessenger, A0, pololu10_150);
    components.emplace_back(new Sonar(uartMessenger, 112)); // 112 = 0x70
    components.emplace_back(new IRSensorAnalog(uartMessenger, A0, pololu10_150));

    LEDStrip *ledStrip = new LEDStrip(uartMessenger, PC_5, 24, 0, 5, 4, 3); // experimentally defined values
    components.emplace_back(ledStrip);
    ledStrip->setMode(1);
    components.emplace_back(new SimpleLED(LED1));

    components.emplace_back(uartMessenger);

    // TODO: ask how to sort this storage

    // sort all components according to their priority
/*    int size = sizeof(components);
    for (int sorted = 0, maxIndex = 0; sorted < size; sorted++) {
        for (int i = 0, max = 0; i < size - sorted; i++) {
            if (components[i]->getPriority() > max) {
                max = components[i]->getPriority();
                maxIndex = i;
            }
        }
        AbstractComponent *buf = components[COMP_NUMBER - sorted];
        components[COMP_NUMBER - sorted] = components[maxIndex];
        components[maxIndex] = buf;
    }*/

    while (true) {
        // Update all components on the board
        for (AbstractComponentPtr& comp : components)
            comp->update();

        Thread::wait(300);
    }
}
