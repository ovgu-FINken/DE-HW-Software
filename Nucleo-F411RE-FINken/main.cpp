#include "mbed.h"
#include "mbed_events.h"
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
#include "algorithm"

// Lookup tables for sensors, pairs {sensorOutput, distance} in acceding order of sensorOutput, distance in millimeters
std::vector<std::vector<int> > pololu10_150 = {{800, 1300},{830, 1000},{900, 800},{1150, 600},{1650, 400},{2700, 200}};

EventQueue queue(16 * EVENTS_EVENT_SIZE); // default value: 32 * EVENTS_EVENT_SIZE
Thread t; // thread for event queue - at the moment is used only by sonars

/*
 * Main function
 */
int main() {
    // If you want to run one of the tests from tests.cpp, just call it here

    // Start the event queue
    t.start(callback(&queue, &EventQueue::dispatch_forever));

    // Initialization of components, connected to the board
    // First parameter for all driver's constructors: uartMessenger
    // Priority of all components by default - 0, can be changed manually. Priority = order of update, lower first
    using AbstractComponentPtr = unique_ptr<AbstractComponent>;
    using Storage = vector<AbstractComponentPtr>;
    Storage components;

    UARTMessenger *uartMessenger = new UARTMessenger(USBTX, USBRX);
    uartMessenger->setPriority(5);

    components.emplace_back(new Sonar(uartMessenger, 112, &queue)); // 112 = 0x70

    components.emplace_back(new IRSensorAnalog(uartMessenger, A0, pololu10_150));

    LEDStrip& ledStrip = *new LEDStrip(uartMessenger, PC_5, 8, 0, 8, 8, 0); // experimentally defined values
    components.emplace_back(&ledStrip);
    ledStrip.setMode(1);
    ledStrip.setColor(0x0000FF, 0);
    ledStrip.setColor(0x0000FF, 1);
    ledStrip.setColor(0x0000FF, 2);
    ledStrip.setColor(0x0000FF, 3);
    ledStrip.setColor(0x00FF00, 4);
    ledStrip.setColor(0xFF0000, 5);
    ledStrip.setColor(0xFF0000, 6);
    ledStrip.setColor(0x00FF00, 7);

    components.emplace_back(new SimpleLED(LED1));

    components.emplace_back(uartMessenger);

    // sort all components according to their priority
    sort(components.begin(), components.end(), [](const AbstractComponentPtr& a, const AbstractComponentPtr& b){return *a < *b;});

    while (true) {
        // Update all components on the board
        for (AbstractComponentPtr& comp : components)
            comp->update();

        Thread::wait(1000);
    }
}
