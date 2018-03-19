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
float rollTolerance = 0.5; //in degrees
float pitchTolerance = 0.5;

//int buttonState;
//int prevState = LOW;

//-----PROTOTYPES-----//
void sense(MikroeAccel202 * ACCEL);
void tune(float * Pgain, float * Dgain, float * limits);

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
    if (abs(accel.pitch) < pitchTolerance)
      pitchBuff[4] = 0;
    else
      pitchBuff[4] = accel.pitch;

    errorSignalPitch = PgainPitch*pitchBuff[4] + (pitchBuff[4] - pitchBuff[3])*DgainPitch;

    if (!isnan(accel.pitch)){
      if( (pulseWidthPitch - errorSignalPitch) < pitch_L) pulseWidthPitch = pitch_L;
      else if (pulseWidthPitch - errorSignalPitch > pitch_H) pulseWidthPitch = pitch_H;
      else pulseWidthPitch -= (int)errorSignalPitch;
    }
    servoPitch.writeMicroseconds(pulseWidthPitch);

    rollBuff[0] = rollBuff[1];
    rollBuff[1] = rollBuff[2];
    rollBuff[2] = rollBuff[3];
    rollBuff[3] = rollBuff[4];
    if (abs(accel.roll) < rollTolerance)
      rollBuff[4] = 0;
    else
      rollBuff[4] = -accel.roll;

    errorSignalRoll = PgainRoll*rollBuff[4] + (rollBuff[4] - rollBuff[3])*DgainRoll;

    if (!isnan(accel.roll)) {
      if ( (pulseWidthRoll-errorSignalRoll) < roll_L) pulseWidthRoll = roll_L;
      else if (pulseWidthRoll - errorSignalRoll >= roll_H) pulseWidthRoll = roll_H;
      else pulseWidthRoll -= (int)errorSignalRoll;
    }
    servoRoll.writeMicroseconds(pulseWidthRoll);

    //TUNING
    /*
    float limits[4];
    limits[0] = 0.1; limits[1] = 1.1;
    limits[2] = 1.0; limits[3] = 8;
    //tune(&PgainRoll, &DgainRoll, limits);
    */
  }
//-----FUNCTION DECLARATIONS-----//
void sense(MikroeAccel202 * ACCEL){
  ACCEL->read();
  ACCEL->calcRoll();
  ACCEL->calcPitch();
}

void tune(float * Pgain, float * Dgain, float * limits){
 /* Function for manual tuning of the PD control.
    *limits -> an array of floats, must be 4 long
    limits[0] = lowerLimitP
    limits[1] = upperLimitP
    limits[2] = lowerLimitD
    limits[3] = upperLimitD   */

  if (sizeof(limits) != sizeof(float)*4) return;
  *Pgain = ((limits[1] - limits[0])/1023)*analogRead(potPin1) + limits[0];
  *Dgain = ((limits[3] - limits[2])/1023)*analogRead(potPin2) + limits[2];
}
