#include <MikroeAccel202.h>

const int pinX = A2; //CHANGE THESE AS NECCESSARY
const int pinY = A1;
const int pinZ = A0;
const int ledPin = 5;

MikroeAccel202 accel(pinX, pinY, pinZ);

void setup()
{
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
}

void loop()
{
    accel.runRotational();
    if (accel.pitch >= 15)
        digitalWrite(ledPin, HIGH);
    else
        digitalWrite(ledPin, LOW);
}

