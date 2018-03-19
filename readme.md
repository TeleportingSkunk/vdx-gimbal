# Two-Axis Camera Stabiliser w/ 9g Servos

Made during my internship at [Vision Dynamix](http://www.visiondynamix.com),  
this gimbal is intended for quad/hexacopter mounting. Using an ADXL335 breakout  
board and an Arduino Nano, the algorithm constantly drives the error signals  
to 0 by modulating the duration of the PWM impulses (in uS).

## Software

Two config branches exist: Master is for the PlatformIO IDE for  
embedded & IoT, while the ARDUINO_IDE branch is for Arduino's official IDE.

Information regarding Atom and PlatformIO can be found here:
* <atom.io>
* <platformIO.org>

Arduino's IDE can be found here:
* <arduino.cc>

## Libraries & Dependencies
I've written a library for interfacing with Mikroelektronika's ADXL330/335  

breakout board. A local version is included in the git itself, but you can  
fork the git itself [here](https://github.com/TeleportingSkunk/MikroeAccel202).  

## Hardware

* 1 x *[Arduino Nano](https://www.aliexpress.com/item/NANO-3-0-controlador-compatible-con-arduino-nano-CH340-turno-USB-controlador-ninguna-CABLE-V3-0/32844003582.html?spm=2114.search0104.3.15.6ab62b20etyeSU&ws_ab_test=searchweb0_0,searchweb201602_3_10152_10151_10065_10068_10344_10342_10343_10340_10341_10696_10084_10083_10618_10307_5711215_10313_10059_10534_100031_10103_10624_10623_443_10622_10621_10620,searchweb201603_1,ppcSwitch_5&algo_expid=f47ce800-4edd-4ce2-ad9a-dbfdfd89b4da-5&algo_pvid=f47ce800-4edd-4ce2-ad9a-dbfdfd89b4da&transAbTest=ae803_4&priceBeautifyAB=0)*

* 1 x *[Mikroelektronika ADXL330 Breakout Board](https://www.mikroe.com/three-axis-accelerometer-board)*

* 2 x *[9g Servos](https://www.aliexpress.com/item/SG90-Servo-RC-Mini-Tower-Pro-Micro-Servo-9g-1-6KG-Servo-SG90-for-RC-250/32584414431.html?spm=2114.search0104.3.14.33a12eb6IxhMyZ&ws_ab_test=searchweb0_0,searchweb201602_3_10152_10151_10065_10068_10344_10342_10343_10340_10341_10696_10084_10083_10618_10307_5711215_10313_10059_10534_100031_10103_10624_10623_443_10622_10621_10620,searchweb201603_1,ppcSwitch_5&algo_expid=18734eb1-df94-4ea5-aaeb-630e54ef782f-2&algo_pvid=18734eb1-df94-4ea5-aaeb-630e54ef782f&transAbTest=ae803_4&priceBeautifyAB=0)*

* 41 x *Male Headers (2 x 15, 1 x 5, 2 x 3)*

* 6 x *Female Headers (2 x 3)*

* 1 x *470uF Capacitor*

* 1 x *[2-pin Screw Terminal](https://www.aliexpress.com/item/20-Set-Lot-5-0MM-PITCH-SPRING-TERMINAL-BLOCKS-CONNECTOR-2-3-4-5-10-20P/32630935499.html?spm=2114.search0104.3.2.73df6b42Ts9Mom&ws_ab_test=searchweb0_0,searchweb201602_3_10152_10151_10065_10068_10344_10342_10343_10340_10341_10696_10084_10083_10618_10307_5711215_10313_10059_10534_100031_10103_10624_10623_443_10622_10621_10620,searchweb201603_1,ppcSwitch_5&algo_expid=305af7e8-b9dc-4edf-8d8f-7631151eb39f-0&algo_pvid=305af7e8-b9dc-4edf-8d8f-7631151eb39f&transAbTest=ae803_4&priceBeautifyAB=0)*


* 2 x *10k - 100k Ohm Potentiometer (for tuning)*
