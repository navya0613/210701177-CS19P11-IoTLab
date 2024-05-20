#include <Servo.h>

// Constants for ultrasonic sensor pins
const int trigPin = 9;   // Trig pin of ultrasonic sensor
const int echoPin = 10;  // Echo pin of ultrasonic sensor

// Constants for servo motor pin and parameters
const int servoPin = 6;  // Pin connected to servo motor
Servo gateServo;         // Servo object for controlling the gate

// Constants for distance thresholds
const int openDistance = 20;    // Distance threshold to open the gate (in cm)
const int closeDistance = 50;   // Distance threshold to close the gate (in cm)

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Attach servo motor to the corresponding pin
  gateServo.attach(servoPin);

  // Set ultrasonic sensor pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize the gate servo position (close the gate)
  gateServo.write(0);
}

void loop() {
  // Measure distance using ultrasonic sensor
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(30);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;  // Convert duration to distance in cm

  // Print distance for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Control gate based on distance thresholds
  if (distance < openDistance) {
    // Open the gate
    gateServo.write(90);  // Adjust angle as needed for your servo
    Serial.println("Gate opened");
  } else if (distance > closeDistance) {
    // Close the gate
    gateServo.write(0);  // Close the gate (adjust angle as needed)
    Serial.println("Gate closed");
  }

  // Delay between distance measurements
  delay(800);  // Adjust delay time as needed
}
