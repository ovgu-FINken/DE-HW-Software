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
     * In case of UARTMessenger itself sends the message to Paparazzi
     */
    virtual void update() = 0;

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

    /**
     * Overloaded comparison operator '<'
     *
     * @param another component for comparison
     * @return true if id is smaller then the id of another component
     */
    bool operator<(const AbstractComponent& another) const;

protected:
    static int s_id;
    int id;
    int priority = 0;
};