#pragma once

#include "mbed.h"

class IRQLock {
public:
    IRQLock() {
        __disable_irq();
    }
    ~IRQLock() {
        __enable_irq();
    }
};