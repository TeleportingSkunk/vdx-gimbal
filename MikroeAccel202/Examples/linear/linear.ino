#include <MeanFilter.h>
#include <MikroeAccel202.h>

int pinX = A2; //CHANGE THESE AS NECCESSARY
int pinY = A1;
int pinZ = A0;
int ledPin = 5;

MikroeAccel202 accel(pinX, pinY, pinZ);

void setup()
{
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
}

void loop()
{
    accel.runLinear();
    if (accel.X >= 12)
      digitalWrite(ledPin, HIGH);
    else
      digitalWrite(ledPin, LOW);
    delay(100);
}

