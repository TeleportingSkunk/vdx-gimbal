#include <ServoReal.h>

#include <MeanFilter.h>
#include <MikroeAccel202.h>

int pinX = A0;
int pinY = A1;
int pinZ = A2;
int potPin1 = A3;
//int potPin2 = A4;
int servoRollPin = 3;
int servoPitchPin = 5;
int buttonPin = 18;
Servo servoRoll;
Servo servoPitch;
/*
int LUTservo[32] = [0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130, 135, 140, 145, 150, 155];

float LUTplatform[32] = [-36.602, -34.067, -31.426, -28.692, -25.880, -23.003, -20.074, -17.108, -14.118, -11.118, -8.121, -5.141, -2.193, 0.710, 3.556, 6.328, 9.015,
                            11.602, 14.076, 16.423, 18.628, 20.679, 22.562, 24.263, 25.767, 27.063, 28.135, 28.970, 29.554, 29.874, 29.915, 29.665];                          
*/

MikroeAccel202 accel(pinX, pinY, pinZ);
unsigned int microWriteRoll = 1500;
unsigned int microWritePitch = 1500;
void sense(MikroeAccel202 * ACCEL);

float gainRoll = 0.3; //tuned 
float gainPitch = 0.6;
float controlSignalRoll, controlSignalPitch;
float rollBuff[5] = {0};
float pitchBuff[5] = {0};
float TdRoll = 5.5; //tuned
float TdPitch = 5.5;
int buttonState;
int prevState = LOW;  

void setup()
{
  servoRoll.attach(servoRollPin); //~~10us/deg
  servoPitch.attach(servoPitchPin);
  Serial.begin(9600);
  servoRoll.writeMicroseconds(microWriteRoll);
  servoPitch.writeMicroseconds(microWritePitch);
  //pinMode(potPin1, INPUT);

  pinMode(buttonPin, INPUT);
  delay(1000);
}
 
void loop()
{
    sense(&accel);
    rollBuff[0] = rollBuff[1];
    rollBuff[1] = rollBuff[2];
    rollBuff[2] = rollBuff[3];
    rollBuff[3] = rollBuff[4];
    if (abs(accel.pitch) < 0.3)
      rollBuff[4] = 0;
    else
      rollBuff[4] = accel.pitch;
    gainRoll = (2.5 - analogRead(potPin1)*0.00244 + .5);
    //TdRoll = (1023-analogRead(potPin2))/70.;

    controlSignalRoll = gainRoll*rollBuff[4] + (rollBuff[4] - rollBuff[3])*TdRoll;
    if (!isnan(accel.pitch)) {
      if ( (microWriteRoll-controlSignalRoll) < 0) microWriteRoll = 0;
      else if (microWriteRoll - controlSignalRoll >= 1750) microWriteRoll = 1750;
      else microWriteRoll -= (int)controlSignalRoll;
      
    }
    servoRoll.writeMicroseconds(microWriteRoll);
 
    pitchBuff[0] = pitchBuff[1];
    pitchBuff[1] = pitchBuff[2];
    pitchBuff[2] = pitchBuff[3];

      pitchBuff[4] = -accel.roll;
    
    controlSignalPitch = gainPitch*pitchBuff[4] + (pitchBuff[4] - pitchBuff[3])*TdPitch;
    if (!isnan(accel.roll)){
      if( (microWritePitch - controlSignalPitch) < 0) microWritePitch = 0;
      else if (microWritePitch - controlSignalPitch >= 1900) microWritePitch = 1900;
      else microWritePitch -= (int)controlSignalPitch;
    }
    servoPitch.writeMicroseconds(microWritePitch);
    //Serial.print(accel.roll); Serial.print("\t"); Serial.print(accel.pitch); Serial.print("\n");
    
    buttonState = digitalRead(buttonPin);
    if ( buttonState == HIGH && prevState == LOW){
      Serial.println(gainRoll);
    }

    prevState = buttonState;
    delay(3);
    }

void sense(MikroeAccel202 * ACCEL){
  ACCEL->read();
  ACCEL->calcRoll();
  ACCEL->calcPitch();
}



