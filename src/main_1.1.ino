
#include <PID_v1.h>
#include <Ultrasonic.h>

const int SERVO_PIN = 9;
const int ULTRASONIC_TRIG_PIN = 10;
const int ULTRASONIC_ECHO_PIN = 11;
const float KP = 2.0;
const float KI = 0.0;
const float KD = 0.0;

// Create the PID controller
PID myPID(&distance, &servoPosition, &setpoint, KP, KI, KD, DIRECT);

float distance = 0.0;
float servoPosition = 90.0;
float setpoint = 90.0;

void setup() {
  Serial.begin(9600);
  pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);
  pinMode(ULTRASONIC_ECHO_PIN, INPUT);
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(100);
  distance = getDistance();
  servoPosition = 90.0;
  Serial.print("Distance: ");
  Serial.println(distance);
  Serial.print("Servo position: ");
  Serial.println(servoPosition);
}
void loop() {
  distance = getDistance();
  float output = myPID.Compute(distance);
  servoPosition += output;
  if (servoPosition < 0) {
    servoPosition = 0;
  } else if (servoPosition > 180) {
    servoPosition = 180;
  }
  analogWrite(SERVO_PIN, servoPosition);
  Serial.print("Distance: ");
  Serial.println(distance);
  Serial.print("Servo position: ");
  Serial.println(servoPosition);
  delay(100);
}
float getDistance() {
  digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
  long echo_time = pulseIn(ULTRASONIC_ECHO_PIN, HIGH);
  float distance = echo_time * 0.0343 / 2.0;
  return distance;
}
