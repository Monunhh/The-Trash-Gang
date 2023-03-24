// Include Libraries
#include "Arduino.h"
#include "NewPing.h"
#include "Servo.h"


// Pin Definitions
#define HCSR04_PIN_TRIG  3
#define HCSR04_PIN_ECHO  2
#define SERVO9G_PIN_SIG  4



// Global variables and defines
const int servo9gRestPosition   = 0;  //Starting position
const int servo9gTargetPosition = 90 //Position when event is detected
// object initialization
NewPing hcsr04(HCSR04_PIN_TRIG,HCSR04_PIN_ECHO);
Servo servo9g;


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    servo9g.attach(SERVO9G_PIN_SIG);
}

void loop()
{
  hcListener(hcsr04.ping_cm());
  delay(60); 
}

void hcListen(int distance)
{
  // distance in cm
  if (distance < 2)
  {
    rotateServo(servo9gTargetPosition);
  } else {
    rotateServo(servo9gRestPosition);
  }
}


void rotateServo(int deg)
{
  servo9g.write(deg);
  // duration for disposal
  delay(1000);  
}