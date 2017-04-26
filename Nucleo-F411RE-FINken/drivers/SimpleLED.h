#pragma once

#include "AbstractComponent.h"

class SimpleLED: public AbstractComponent {
public:
    SimpleLED();
    virtual void update();

private:
    DigitalOut led;
};