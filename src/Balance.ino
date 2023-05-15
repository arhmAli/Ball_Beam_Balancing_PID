#include <Servo.h>

// Ultrasonic sensor pins
const int trigPin = 6;
const int echoPin = 7;

// Servo motor pins
const int servoPin = 9;

// Constants for PID control
const double Kp = 6;  // Proportional constant
const double Ki = 0.0;  // Integral constant
const double Kd = 1.5;  // Derivative constant

// Variables for PID control
double setpoint = 50/2;  // Desired position in centimeters
//double setpoint = 30;  // Desired position in centimeters
double input = 0.0;      // Current position in centimeters
double output = 0.0;     // Servo motor angle
double error = 0.0;      // Position error
double previousError = 0.0;
double integral = 0.0;
double derivative = 0.0;

Servo servo;

void setup() {
  // Initialize the servo motor
  Serial.begin(9600);
  servo.attach(servoPin);
  
  // Initialize the ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Set the initial position of the servo motor
  servo.write(130);  // Zero degree position
}

void loop() {
  // Read the current position from the ultrasonic sensor
  double duration, distance;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration * 0.034 / 2.0;  // Calculate distance in centimeters
  Serial.println(distance);
  delay(100);
