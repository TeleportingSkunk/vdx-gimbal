#include <Arduino.h>
#include <MikroeAccel202.h>
#include <Servo.h>
//-----PINS------//
const int pinX = A0;
const int pinY = A1;
const int pinZ = A2;
const int servoRollPin = 5;
const int servoPitchPin = 3;

//TUNING PINS
const int potPin1 = A3;
const int potPin2 = A4;
const int buttonPin = 18;

//-----VARIABLES-----//

/* Object init block. MikroeAccel202 is a custom library for interfacing with the
  ADXL335 for the Mikroelektronika 2.02 breakout board*/
Servo servoRoll;
Servo servoPitch;
MikroeAccel202 accel(pinX, pinY, pinZ);
float rollBuff[5] = {0}; //data buffers
float pitchBuff[5] = {0};

/* This block contains EXPERIMENTALLY gleaned values regarding the maximum and minimum
   strokes of the servos(limited by the gimbal mechanism itself)
   Expressed as the width of the PWM ON portion in microseconds.*/
unsigned int roll_L = 250;
unsigned int roll_H = 1900;
unsigned int pitch_L = 250;
unsigned int pitch_H = 1900;

/* Initial values for servo positions */
unsigned int pulseWidthRoll = 1500;
unsigned int pulseWidthPitch = 1500;

/* Control system parameters block. All values MUST be tuned experimentally using
the provided tune() function and potentiometer inputs to A3 & A4. */
float errorSignalRoll, errorSignalPitch; //measured error value based on accel readings.
float PgainRoll = 0.6; //proportional gain for the roll servo
float PgainPitch = 0.3; //proportional gain for the pitch servo
float DgainRoll = 5.5; //tuned
float DgainPitch = 5.5;

//int buttonState;
//int prevState = LOW;

//-----PROTOTYPES-----//
void sense(MikroeAccel202 * ACCEL);
void tune();

void setup()
{
  //CORE FUNCTIONALITIES
  servoRoll.attach(servoRollPin); //~~10us/deg
  servoPitch.attach(servoPitchPin);
  servoRoll.writeMicroseconds(pulseWidthRoll); //initial positions.
  servoPitch.writeMicroseconds(pulseWidthPitch);

  //TUNING
  Serial.begin(9600);
  pinMode(potPin1, INPUT);
  pinMode(potPin2, INPUT);
  pinMode(buttonPin, INPUT);

  delay(200);
}

void loop()
{
    sense(&accel);

    pitchBuff[0] = pitchBuff[1];
    pitchBuff[1] = pitchBuff[2];
    pitchBuff[2] = pitchBuff[3];
    pitchBuff[3] = pitchBuff[4];
    if (abs(accel.pitch) < 0.5)
      pitchBuff[4] = 0;
    else
      pitchBuff[4] = accel.pitch;

    //PgainRoll = (2.5 - analogRead(potPin1)*0.00244 + .5);
    //DgainRoll = (1023-analogRead(potPin2))/70.;

    errorSignalRoll = PgainRoll*rollBuff[4] + (rollBuff[4] - rollBuff[3])*DgainRoll;
    if (!isnan(accel.pitch)) {
      if ( (pulseWidthRoll-errorSignalRoll) < 0) pulseWidthRoll = 0;
      else if (pulseWidthRoll - errorSignalRoll >= 1750) pulseWidthRoll = 1750;
      else pulseWidthRoll -= (int)errorSignalRoll;

    }
    servoRoll.writeMicroseconds(pulseWidthRoll);

    rollBuff[0] = rollBuff[1];
    rollBuff[1] = rollBuff[2];
    rollBuff[2] = rollBuff[3];
    rollBuff[3] = rollBuff[4];
    if (abs(accel.roll) < 0.5)
      pitchBuff[4] = 0;
    else
      pitchBuff[4] = -accel.roll;

    errorSignalPitch = PgainPitch*pitchBuff[4] + (pitchBuff[4] - pitchBuff[3])*DgainPitch;
    if (!isnan(accel.roll)){
      if( (pulseWidthPitch - errorSignalPitch) < 0) pulseWidthPitch = 0;
      else if (pulseWidthPitch - errorSignalPitch >= 1900) pulseWidthPitch = 1900;
      else pulseWidthPitch -= (int)errorSignalPitch;
    }
    servoPitch.writeMicroseconds(pulseWidthPitch);
    //Serial.print(accel.roll); Serial.print("\t"); Serial.print(accel.pitch); Serial.print("\n");

    /*buttonState = digitalRead(buttonPin);
    if ( buttonState == HIGH && prevState == LOW){
      Serial.println(PgainRoll);
    }

    prevState = buttonState;
    delay(3);
    }
    */
  }
//-----FUNCTION DECLARATIONS-----//
void sense(MikroeAccel202 * ACCEL){
  ACCEL->read();
  ACCEL->calcRoll();
  ACCEL->calcPitch();
}
