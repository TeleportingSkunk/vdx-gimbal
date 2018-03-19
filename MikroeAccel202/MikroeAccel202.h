#ifndef _MIKROE_ACCEL202_H
#define _MIKROE_ACCEL202_H

#include <math.h>
#include "MeanFilter.h"
#include <Arduino.h>
#define Q int
#define N 8

class MikroeAccel202
{
 private:
    int pinX, pinY, pinZ;
    bufferMean<Q, N> meanX, meanY, meanZ;
 public:
    
    int X, Y, Z;
    int bias;
    float roll, pitch, yaw;

    MikroeAccel202(int pinX, int pinY, int pinZ);
    
    void run();

    void runLinear();

    void runRotational();

    void read();

    void calc();
 
    float calcRoll();

    float calcPitch();

    float calcYaw();

    void dumpLinear();

    void dumpRotational();

};
#endif
