#pragma once

enum ComponentType {
    SONAR,
    IRANALOG,
    IRDIGITAL
};

struct SubMessage {
    /**
     * type of the message:
     * 0 - Sonar
     * 1 - IR Sensor analog
     * 2 - IR Sensor digital
     */
    uint8_t type;
    uint8_t id;
    uint8_t length;
    uint8_t* data;
};