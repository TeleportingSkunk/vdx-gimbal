# Two-Axis Camera Stabiliser w/ 9g Servos

Made during my internship at [Vision Dynamix](http://www.visiondynamix.com), this gimbal is intended for quad/hexacopter mounting. Using an ADXL335 breakout board and an Arduino Nano, the algorithm constantly drives the error signals to 0 by modulating the duration of the PWM impulses (in uS).

## Software
Two config branches exist: Master is for the PlatformIO IDE for embedded & IoT, while the ARDUINO_IDE branch is for Arduino's official IDE.

Information regarding Atom and PlatformIO can be found here:
* <http://atom.io>
* <http://platformIO.org>

Arduino's IDE can be found here:
* <http://arduino.cc>

## Libraries & Dependencies
I've written a library for interfacing with Mikroelektronika's ADXL330/335 breakout board. A local version is included in the git itself, but you can fork the git itself [here](https://github.com/TeleportingSkunk/MikroeAccel202).  

## Hardware
* 1 x *[Arduino Nano](https://www.aliexpress.com/item/NANO-3-0-controlador-compatible-con-arduino-nano-CH340-turno-USB-controlador-ninguna-CABLE-V3-0/32844003582.html?spm=2114.search0104.3.15.6ab62b20etyeSU&ws_ab_test=searchweb0_0,searchweb201602_3_10152_10151_10065_10068_10344_10342_10343_10340_10341_10696_10084_10083_10618_10307_5711215_10313_10059_10534_100031_10103_10624_10623_443_10622_10621_10620,searchweb201603_1,ppcSwitch_5&algo_expid=f47ce800-4edd-4ce2-ad9a-dbfdfd89b4da-5&algo_pvid=f47ce800-4edd-4ce2-ad9a-dbfdfd89b4da&transAbTest=ae803_4&priceBeautifyAB=0)*

* 1 x *[Mikroelektronika ADXL330 Breakout Board](https://www.mikroe.com/three-axis-accelerometer-board)*

* 2 x *[9g Servos](https://www.aliexpress.com/item/SG90-Servo-RC-Mini-Tower-Pro-Micro-Servo-9g-1-6KG-Servo-SG90-for-RC-250/32584414431.html?spm=2114.search0104.3.14.33a12eb6IxhMyZ&ws_ab_test=searchweb0_0,searchweb201602_3_10152_10151_10065_10068_10344_10342_10343_10340_10341_10696_10084_10083_10618_10307_5711215_10313_10059_10534_100031_10103_10624_10623_443_10622_10621_10620,searchweb201603_1,ppcSwitch_5&algo_expid=18734eb1-df94-4ea5-aaeb-630e54ef782f-2&algo_pvid=18734eb1-df94-4ea5-aaeb-630e54ef782f&transAbTest=ae803_4&priceBeautifyAB=0)*

* 41 x *Male Headers (2 x 15, 1 x 5, 2 x 3)*

* 6 x *Female Headers (2 x 3)*

* 1 x *470uF Capacitor*

* 1 x *[2-pin Screw Terminal](https://www.aliexpress.com/item/20-Set-Lot-5-0MM-PITCH-SPRING-TERMINAL-BLOCKS-CONNECTOR-2-3-4-5-10-20P/32630935499.html?spm=2114.search0104.3.2.73df6b42Ts9Mom&ws_ab_test=searchweb0_0,searchweb201602_3_10152_10151_10065_10068_10344_10342_10343_10340_10341_10696_10084_10083_10618_10307_5711215_10313_10059_10534_100031_10103_10624_10623_443_10622_10621_10620,searchweb201603_1,ppcSwitch_5&algo_expid=305af7e8-b9dc-4edf-8d8f-7631151eb39f-0&algo_pvid=305af7e8-b9dc-4edf-8d8f-7631151eb39f&transAbTest=ae803_4&priceBeautifyAB=0)*

* 2 x *10k - 100k Ohm Potentiometer (for tuning)*

* 1 x *Push-button (for tuning)*

## Usage
Once you've setup the hardware and prepared the IDE, flash the Arduino and power it externally at 5 - 6.5 V. No need for usb-serial connection unless tuning.

### PD Tuning Guide
Line 111 of main.cpp contains a commented block for PD tuning. Hardware-wise, this will require two potentiometers acting as voltage dividers, feeding the divided voltage into the 10-bit ADCs at pins A3 and A4, as per the original code.
To tune the system:
1. Uncomment the tuning block
2. Set the values of the limits array to represent the minimum and maximum ranges for proportional and derivative gain, respectively. The variable names are self explanatory.
3. Wire up two potentiometers (minimum 10k Ohm) as ***5V voltage dividers*** to the pins A3 and A4 and a push button to pin 2.
4. Run the code and follow the following method:
  1. Set all gains to minimum values.
    * If the system is already unstable, change your limits
  2. Increase the **P gain** until stable oscillations arise upon a step input.
  3. Increase the **D gain** until the damping is critical, i.e. the oscillations have vanished and there's no overshoot
  4. Repeat steps 2 and 3 until the desired rise time is achieved.
    * Rapid miniscule oscillations are the result of an overlarge **D gain**.
    * You may have to reset the limits to reach higher (or lower) gains.
  5. Press the button to print the current gain values to the serial monitor. Save these numbers and add them to the control variable initialisation block.
  6. Re-comment the tuning block.

## Contributors
* Marko Galevski
  * [Github](http://github.com/TeleportingSkunk)
  * [LinkedIn](https://www.linkedin.com/in/marko-galevski/)
* Tomislav Dimitrievski - Thanks for the help with improving the PCB design
* Stole Jovanovski - Thanks for developing the mean filter library, and general advice
  * [LinkedIn](https://www.linkedin.com/in/stole-jovanovski/)

## About ***Vision Dynamix***
Vision Dynamix is a software company that develops mapping software for unmanned aerial vehicles based on computer vision and 3D scene reconstruction.

#### Contact
Email: contact@visiondynamix.com

Phone: +389 71 620 937

Address: Ruger Boskovic 18, 1000 Skopje, Macedonia
