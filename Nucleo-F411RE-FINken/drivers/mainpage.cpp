/*! \mainpage Hardware Development for FINken Page
 *
 * \section intro_sec Introduction-Hardware Development for FINken Robots
 *
 * Our project is to develop hardware for the FINken 3 robots.

 * We have designed the PCBs where the refernce link is given below for the further details  
 <a href="https://github.com/ovgu-FINken/DE-HW-Hardware/wiki">link text</a> 

 *This document mainly focused on the software part.

 *Currently the FINken III is the newest generation of our copters with more power,better communication and more sensors

*<b>Specifications:</b>

1. Optical flow sensor with sonar ranging towards ground
   (Optional: Infrared distance sensor towards ground)
2. Tower of 4  sonar ranging sensor
3. 802.15.4 based phase-difference ranging between copters and anchors
4. PaparazziUAV board (Lisa/M 2.1) - with floating point support
5. 802.15.4 Communication Modul to communicate to ground station and between copters

 *
 * \section Software_sec Software Development
    __________________________________________________
 *                     
 * \subsection comp_sec Components used in our project
    __________________________________________________               

 *List of components are provided below:

1. Optical flow sensor with sonar ranging towards ground
2. 8 Sonars ranging sensors
3. PaparazziUAV board
4. RGB LEDs
5. Illuminating Sensor
6. STM32F44RET6 Micro controller

 * \section about Programming language and installation guide for using in Linux

*We programmed in Clion using mbed libraries in C++ language.For using mbed libraries,mbed cli needs to installed for experting into IDE.

*<b>Installing mbed-cli</b>

1. Install Python v2.7
2. Install Git and Mercurial
3. Install GNU ARM Embedded Toolchain
Step0: Remove previous version of toolchains, if needed
		"sudo apt-get remove gcc-arm-none-eabi"
		"sudo apt-get remove g++-arm-linux-gnueabi"
		"sudo apt-get remove binutils-arm-none-eabi"
Step1: Inside Ubuntu, open a terminal and input
       "sudo add-apt-repository ppa:team-gcc-arm-embedded/ppa"

Step2: Continue to input
       "sudo apt-get update"

Step3: Continue to input to install toolchain
       "sudo apt-get install gcc-arm-embedded"
4. Install mbed-cli
		"sudo pip install mbed-cli"
5. Get the program
6. Select tollchain in mbed-cli. Run in folder my_program/mbed_os
		"mbed config --global GCC_ARM_PATH /usr/bin/"
7. Compile the programm. Run in my_program folder
		"mbed compile -t GCC_ARM -m NUCLEO_F411RE"
8. Flash the microcontroller

9.Use anotherterminal for running the code (for convinence) for gdb terminal

(gdb) target extended-remote /dev/ttyACM0
Remote debugging using /dev/ttyACM0
If ACM0 doesnt work need to try for ACM1 and ACM2  
(gdb) monitor swdp_scan....For supplying power
Target voltage: 3.4V 
Device   IDCODE      Description
1       0x06413041  ST Microelectronics: STM32F4xx.

Available Targets:
No. Att Driver
 1      STM32F4xx

(gdb) attach 1
load the .elf file
run
if u want to break the code and check we can do the particular check

Open gtk terminal where one can see the output give the port ACM0 and change to hex to binary to see the output in binary
(in bytes)
 |Sensor    |Type of sensor   |Id of the sensor|  length of mesaage |  
 |:-------- |:--------------: |:--------------:|-------------------:|
 |Sonar     |  1 byte         |   1 byte       |         4          |
 |IRsensor  |  1 byte         |   1 byte       |         2          |
 |LEDstrip  |  1 byte         |   1 byte       |         4          | 

We first went with each sensor and then integrated the components.
In program we used UART messenger as constructor for all the components 
Priority of the message will be according to the order of the udpdate
      
*/       

/**

* \page page_name WS2812 Detailed Description
* \subpage subpage_name LED

1. WS2812B is a intelligent control LED light source that the control circuit and RGB chip are integrated. 
2. Here we can control the brightness by using the pixel of each colour RGB
3. Component LED is pciked from the all other components to give a display of receiving data to the paparazzi.
   LED is ON where we can set number of LEDs to glow.Each led can also be set with particular color and brightness too.
   GTK terminal in Linux(Ubuntu) can be used to simulate the behaviour of paparazzi response by receiving the data from the microcontroller
7. We had to give data transfer time to set the LEd glow
8. LED with low driving voltage, environmental protection and energy saving, high brightness,good consistency,low power,long life. 

Here is image of the sonar we used
   *  \image html ws2812.jpg


|NO.| Symbol|   Function description      |
|--:|:---:  |:--------------------------- |
|1  |  VDD  | Power supply LED            |
|2  |  DOUT |  Control data signal output |
|3  |  VSS  |Ground                       |
|4  |  DIN  | Control data signal input   |
   
     
*\section Data_sec Data tranfer Time( TH+TL=1.25&mu;s &plusmn; 600ns)

|   | Explanation	       |Times     |±delay         |
|--:| :---------------------:  | :------: |:------------- |                
|T0H| 0 code ,high voltage time|0.4&mu;s  | &plusmn;150ns |
|T1H| 1 code ,high voltage time|0.8&mu;s  | &plusmn;150ns |
|T0L| 0 code , low voltage time|0.85&mu;s | &plusmn;150ns |
|T1L| 1 code ,low voltage time |0.45&mu;s | &plusmn;150ns |
|RES| low voltage time 	       |Above 50µs|               |


The refernce link of the datasheet for the further details  
 <a href="https://cdn-shop.adafruit.com/datasheets/WS2812.pdf">link text</a> 


* \page page_name1 I2CXL-MAX SONAR Detailed description
* \subpage subpage_name1 MB1232

*General description:

1. The I2CXL-MaxSonar-EZ series ultrasonic sensors with an easy to use I2C 
2. These sensors have a high acoustic power output along with real-time auto calibration for changing conditions 
   (voltage and acoustic or electric noise) that ensure users receive the most reliable (in air) ranging data for every reading taken. 
3. The low power 3V – 5.5V operation provides very short to long-range detection and ranging
4. It detect objects from 0-cm* to 765-cm (25.1 feet) and provide sonar range information from 20-cm or 25-cm out 
   to 765-cm with 1-cm resolution. Objects from 0-cm* to minimum distance typically range as minimum distance.

Here is image of the sonar we used
   *  \image html sonar.jpg

The below is the graph for the ranges and the number of trials we have taken



*Features :-

1. I2C bus communication allows rapid control of multiple sensors with only two wires.
2. We use 8 sonar sensors where these sonars will maintain the copter in the air without any obstruction and will sense the ranging distance in the arena.
3  Sensors are placed in such a way that it will detect the distance from all possible sides 
5. Range information starting at min. distance
6. 3V to 5.5V supply with very low average current draw 
7.Status pin available to determine sensor state 
8.Power-up address reset pin available

Here is a diagramatic view if we view copter from top(we can c sonars connceted in this pattern)
   *  \image html Untitled.png


The refernce link of the datasheet for the further details  
 <a href="http://www.maxbotix.com/documents/I2CXL-MaxSonar-EZ_Datasheet.pdf">link text</a>



* \page IR DISTANCE GP2Y0A605: Detailed description
* \subpage GP2Y0A605

1.GP2Y0A60SZ0F is a distance measuring sensor unit, composed of an integrated combination of PSD (position sensitive detector) ,
IR-LED (infrared emitting diode) and signal processing circuit.
2.The variety of the reflectivity of the object, the environmental temperature and the operating duration are not influenced 
easily to the distance detection because of adopting the triangulation method.
3.This device outputs the voltage corresponding to the detection distance. So this sensor can also be used as a proximity sensor.
4.We use on the bottom part of the copter which will use the to detect the height of the copter when it fly.
5.Distance measuring range is 10cm to 150cm.
6.It has long distacne measuring type(No external control signal required)
7.The output is Analog type

Here is the image of IR sensor we used
   *  \image html shopping.jpg

|Parameter                |Symbol   | Conditions              | MIN.| MAX.|Unit   |
|------------------------:|:-------:|:-----------------------:|:---:|:---:|:-----:|
|Measuring distance range |&Delta;L |                         | 10  | 150 | cm    |
|Output terminal voltage  |Vo       |L=150cm                  | 0.15| 1.15| V     |
|Output voltage difference|&Delta;Vo|Output change at L change|     |     |       |
|                         |         |(10cm - 150cm)           | 2.75| 3.25| V     |
|Average supply current   |Icc1     |Vcc=5V, VCTRL =5V        | -   |  50 | mA    |
|Stand-by supply current  | Icc2    |Vcc=5V, VCTRL =0V        | -   |   5 | &mu;A |

further details about the component,datasheet is in the below link
<a href="https://www.pololu.com/file/0J812/gp2y0a60szxf_e.pdf">link text</a> 


*/




