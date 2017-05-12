#pragma once

#include "mbed.h"
#include "PinNames.h"
#include "SubMessage.h"
#include "atomic"

class AbstractComponent {
public:
    /**
     * Main function for using all the components.
     * Update component data and add this information to UARTMessenger.
     */
    virtual void update() = 0;

    /**
     * React to the message from Paparazzi.
     * At the moment only relevant for LED strip
     *
     * @param msg Message from Paparazzi
     */
    virtual void onPaparazziMsg(uint8_t* msg) {
        return;
    };

    /**
     * Set priority to the component, used for updating order
     *
     * @param p priority
     */
    void setPriority(int p) {
        priority = p;
    }

    /**
     * @return priority of the component
     */
    int getPriority() {
        return priority;
    }

    int id;

    bool operator<(const AbstractComponent& another) const;

protected:
    int priority = 0;
    static int s_id;
};