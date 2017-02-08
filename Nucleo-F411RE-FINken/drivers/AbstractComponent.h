#pragma once

class AbstractComponent {
public:
    virtual void update() = 0;
    int getPriority() {
        return priority;
    }

protected:
    int priority;
};