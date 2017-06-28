#ifndef PixelArray_H
#define PixelArray_H

#include "mbed.h"

//!Library for the WS2812 RGB LED with integrated controller
/*!
PixelArray
*/
class PixelArray
{
public:
    //!Creates an instance of the class.
    /*!
    Pixel Array
    */
    PixelArray(int);

    /*!
    Destroys instance.
    */
    ~PixelArray();

    int* getBuf();

    void SetAll(unsigned int);
    void SetAllI(unsigned char);
    void SetAllR(unsigned char);
    void SetAllG(unsigned char);
    void SetAllB(unsigned char);

    // location, value
    void Set(int, unsigned int);
    void SetI(int, unsigned char);
    void SetR(int, unsigned char);
    void SetG(int, unsigned char);
    void SetB(int, unsigned char);

private:

    int *pbuf;
    int pbufsize;

    void __set_pixel_component(int index, int channel, int value);
    void __set_pixel(int index, int value);

};

#endif

