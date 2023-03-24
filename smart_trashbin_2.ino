// Include Libraries
#include <Arduino.h>
#include <Servo.h>


// Pin Definitions
#define HCSR04_PIN_TRIG  3
#define HCSR04_PIN_ECHO  2
#define SERVO9G_PIN_SIG  4



// Global variables and defines
const int servo9gRestPosition   = 0;  //Starting position
const int servo9gTargetPosition = 135; //Position when event is detected
const int triggeredDist = 80; // Triggered position for scanner (cm)
// object initialization
Servo servo;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    pinMode(HCSR04_PIN_TRIG, OUTPUT);
    pinMode(HCSR04_PIN_ECHO, INPUT);
    servo.attach(SERVO9G_PIN_SIG);
}

void loop()
{
  // 0.01723 times the output of the ultra sonic reader gives us the required
  hcListener(readUltrasonicDistance(HCSR04_PIN_TRIG, HCSR04_PIN_ECHO) * 0.01723);
  delay(60); 
}

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void hcListener(int distance)
{
  // distance in cm
  if (distance < triggeredDist)
  {
    rotateServo(servo9gTargetPosition);
  } else {
    rotateServo(servo9gRestPosition);
  }
}


void rotateServo(int deg)
{
  servo.write(deg);
  // duration for disposal 
}