#include <Ultrasonic.h>
#include <PS4Controller.h>
#include <ESP32Servo.h>

// Pins for ultrasonic sensor
#define TRIG_PIN 14
#define ECHO_PIN 12

// LED for obstacle alert
#define LED_PIN 15

// Metal detection pin
#define METAL_SENSOR_PIN 34  // Use any available analog/digital pin

// Define servo objects
Servo servo1, servo2, servo3, servo4, servo5;

// Servo motor pins
const int servoPin1 = 27;
const int servoPin2 = 26;
const int servoPin3 = 25;
const int servoPin4 = 32;
const int servoPin5 = 33;

// H-Bridge motor driver pins
const int motor1Pin1 = 18;
const int motor1Pin2 = 5;
const int motor1EN = 19;  // PWM-capable
const int motor2Pin1 = 17;
const int motor2Pin2 = 16;
const int motor2EN = 4;   // PWM-capable

Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);

void setup() {
  Serial.begin(115200);

  // Connect PS4 Controller
  if (!PS4.begin("94:b5:55:f8:18:ba")) {
    Serial.println("PS4 controller not connected!");
    while (true);
  }
  Serial.println("PS4 controller connected!");

  // Attach servos
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  servo4.attach(servoPin4);
  servo5.attach(servoPin5);

  // Motor pins
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor1EN, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor2EN, OUTPUT);

  // Additional sensors
  pinMode(LED_PIN, OUTPUT);
  pinMode(METAL_SENSOR_PIN, INPUT);
}

void loop() {
  if (PS4.isConnected()) {
    // Distance Measurement
    float distance_cm = ultrasonic.distanceRead(CM);

    // Servo Mapping
    int servo1Pos = map(PS4.LStickY(), -128, 127, 0, 180);
    int servo2Pos = map(PS4.LStickX(), -128, 127, 0, 180);
    int servo3Pos = map(PS4.RStickY(), -128, 127, 0, 180);
    int servo5Pos = map(PS4.RStickX(), -128, 127, 0, 180);
    int servo4Pos = map(PS4.L2Value(), 0, 255, 0, 180); // Corrected mapping

    // Write to Servos
    servo1.write(servo1Pos);
    servo2.write(servo2Pos);
    servo3.write(servo3Pos);
    servo4.write(servo4Pos);
    servo5.write(servo5Pos);

    // Obstacle LED alert
    if (distance_cm > 0 && distance_cm < 10) {
      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);
      delay(100);
    } else {
      digitalWrite(LED_PIN, LOW);
    }

    // Metal Detection
    int metalDetected = digitalRead(METAL_SENSOR_PIN);
    if (metalDetected == HIGH) {
      Serial.println("⚠️ Metal Detected!");
    }

    // Motor Control with Buttons
    int motorSpeed = 180;  // PWM value (0-255)

    if (PS4.Triangle()) { // Forward
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
    } else if (PS4.Cross()) { // Backward
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
    } else if (PS4.Square()) { // Left
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
    } else if (PS4.Circle()) { // Right
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
    } else { // Stop
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
    }

    // Motor Speed Control
    analogWrite(motor1EN, motorSpeed);
    analogWrite(motor2EN, motorSpeed);

    // Debugging
    Serial.print("Distance: ");
    Serial.print(distance_cm);
    Serial.print(" cm | Metal: ");
    Serial.println(metalDetected == HIGH ? "YES" : "NO");
    delay(10);
  }
}
