#include <Servo.h>

int servoPin = 9;    // The pin to which the servo signal wire is connected
int minPos = 40;     // Minimum position in degrees
int maxPos = 140;    // Maximum position in degrees

int E1 = 5;
int M1 = 4;
int E2 = 3;
int M2 = 2;

Servo servo;

void setup() {
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);

  servo.attach(servoPin);  // Attaches the servo object to the specified pin
  Serial.begin(9600);      // Initialize serial communication at 9600 baud rate
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); // Read the input from the serial monitor
    
    switch (input.toInt()) {
      case 1:
        moveForward();
        break;
        
      case -1:
        moveBackward();
        break;
        
      case 0:
        stopMotors();
        break;
        
      default:
        int angle = input.toInt(); // Convert the input to an integer
        moveServo(angle);
        break;
    }
  }
}

void moveBackward() {
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 300); // Full speed forward for motor 1
  analogWrite(E2, 300); // Full speed forward for motor 2
}

void moveForward() {
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, 255); // Full speed backward for motor 1
  analogWrite(E2, 255); // Full speed backward for motor 2
}

void stopMotors() {
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, 0); // Stop motor 1
  analogWrite(E2, 0); // Stop motor 2
}

void moveServo(int angle) {
  angle = constrain(angle, minPos, maxPos);
  servo.write(angle);
}
