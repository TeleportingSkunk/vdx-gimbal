#include <math.h>
#include "MikroeAccel202.h"
#include <Arduino.h>
#define Q int
#define N 8


    MikroeAccel202::MikroeAccel202(int pinX, int pinY, int pinZ)
    {
      this->pinX = pinX;
      this->pinY = pinY;
      this->pinZ = pinZ;

      pinMode(pinX, INPUT);
      pinMode(pinY, INPUT);
      pinMode(pinZ, INPUT);
      bias = 292;

      pitch = roll = yaw = 0;

      X = analogRead(pinX);
      Y = analogRead(pinY);
      Z = analogRead(pinZ);

      meanX.init(X);
      meanY.init(Y);
      meanZ.init(Z);

    }
    
    void MikroeAccel202::run()
    {
        this->runRotational();
        this->dumpLinear();
    }

    void MikroeAccel202::runLinear()
    {
        this->read();
        this->dumpLinear();
    }

    void MikroeAccel202::runRotational()
    {
        this->read();
        this->calc();
        this->dumpRotational();
    }

    void MikroeAccel202::read()
    {
      X = meanX.update(analogRead(pinX)) - bias;
      Y = meanY.update(analogRead(pinY)) - bias;
      Z = meanZ.update(analogRead(pinZ)) - bias;

      roll = pitch = 0;
    }

    void MikroeAccel202::calc()
    {
        this->calcRoll();
        this->calcPitch();
        this->calcYaw();
    }
    float MikroeAccel202::calcRoll()
    {
      if (roll != 0) return roll;

      roll = atan2(Y, sqrt(Z * Z + X * X)) * 180. / M_PI;
      return roll;
    }

    float MikroeAccel202::calcPitch()
    {
      if (pitch != 0) return pitch;
      pitch = atan2(X, sqrt(Y * Y + Z * Z)) * 180. / M_PI;
      return pitch;
    }

    float MikroeAccel202::calcYaw()
    {
      if (yaw != 0) return yaw;
      yaw = atan2(Z, sqrt(X * X + Y * Y)) * 180./ M_PI;
      return yaw;
    }

    void MikroeAccel202::dumpLinear()
    {
        Serial.print(X); Serial.print('\t'); Serial.print(Y); Serial.print('\t'); 
        Serial.print(Z); Serial.print('\n'); 
    }
    void MikroeAccel202::dumpRotational()
    { 
        Serial.print(roll); Serial.print('\t'); Serial.print(pitch); Serial.print('\t');
        Serial.print(yaw); Serial.print('\n');
    }
