#include "IRSensorDigital.h"

/**
	* @param dataPin - pin on board, where data pin of IR sensor is connected
	* @param detectionRange - distance of detection for this sensor
*/

IRSensorDigital::IRSensorDigital(UARTMessenger *const uartMsngr, PinName pin, float detectionRange):uartMessenger(uartMsngr),dataPin(pin),sensor(dataPin) {
    id = ++s_id;
    this->detectionRange = detectionRange;
    inRange = false;
};

/**

	*if the value is less than the detectionRange then it will return the true value

	* SubMessage type is IRDIGITAL,Id of the sensor

	*reinterpret_cast is that  submessgae.data will be converting into boolean 
         Returns a value of type boolean

	*Length is size inRange

  	*Append the message

*/


void IRSensorDigital::update() {
    float value = sensor.read();
    if (value > detectionRange) {
        inRange = false;
    } else {
        inRange = true;
    }

    subMessage.type = IRDIGITAL;
    subMessage.id = id;
    reinterpret_cast<bool*>(subMessage.data)[0] = inRange;
    subMessage.length = sizeof(inRange);

    uartMessenger->appendMessage(subMessage);
}

bool IRSensorDigital::isInRange() {
    return inRange;
}





