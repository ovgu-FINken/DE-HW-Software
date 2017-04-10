#pragma once

#include "mbed.h"

class AbstractComponent {
public:
    virtual void update() = 0;
    void onPaparazziMsg(uint8_t* msg);
    void setPriority(int p) {
        priority = p;
    }
    int getPriority() {
        return priority;
    }

protected:
    int priority = 0;
};