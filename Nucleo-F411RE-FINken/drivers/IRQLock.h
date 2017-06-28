#pragma once

#include "mbed.h"
/** 

	*In some cases, we want to ensure a section of code is not interrupted.

	*For example, you might be talking to a peripheral where the whole transaction must happen in one go, 
         and an interrupt could cause the operation to fail.

	*So we use the constructor and deconstructor of IRQ Lock

*/ 

class IRQLock {

public:
    IRQLock() 

/** 

	*We use constructor for IRQlock where we disable the the request 

*/
	{
        __disable_irq(); //Disable Interrupts
        }

    ~IRQLock() 
/** 
  	*deconstructor where we enable the interrupts 
*/
 	{
        __enable_irq(); //Enable Interrupts
    	}
};