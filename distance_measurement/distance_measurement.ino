#include <LiquidCrystal.h> // Load Liquid Crystal Library

// Initialize the LCD with the pin configuration
LiquidCrystal LCD(11, 10, 9, 2, 3, 4, 5); // (RS, R/W, E, DB4, DB5, DB6, DB7)

// Define pins for the ultrasonic sensor
#define trigPin 13 // Sensor Trigger pin connected to Arduino pin 13
#define echoPin 12 // Sensor Echo pin connected to Arduino pin 12

// Define pins for the LEDs
const int ledPin1 = 6; // LED for distance 0-15 cm
const int ledPin2 = 7; // LED for distance 16-30 cm
const int ledPin3 = 8; // LED for distance 31-45 cm

// Define intervals for LEDs blinking
const long interval1 = 100; // Interval for LED1 (milliseconds)
const long interval2 = 75;  // Interval for LED2 (milliseconds)
const long interval3 = 50;  // Interval for LED3 (milliseconds)

// Variables for timing
unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;

void setup() {
  pinMode(trigPin, OUTPUT);  // Set the trigger pin as an output
  pinMode(echoPin, INPUT);   // Set the echo pin as an input

  pinMode(ledPin1, OUTPUT);  // Set the LED pins as outputs
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  LCD.begin(16, 2); // Initialize LCD with 16 columns and 2 rows
  LCD.setCursor(0, 0); // Set cursor to top-left corner
  LCD.print("Target Distance:"); // Print initial message

  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  long duration;
  int distance;

  // Send a pulse to the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the pulse from the echo pin
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  distance = (duration / 2) / 29.1;

  // Display distance on LCD
  LCD.setCursor(0, 1); // Set cursor to the first column of the second row
  LCD.print("                "); // Clear previous distance
  LCD.setCursor(0, 1); // Reset cursor position
  LCD.print(distance); // Print the measured distance
  LCD.print(" cm"); // Print the units

  unsigned long currentMillis = millis(); // Get the current time

  // Control LED1 based on distance range 0-15 cm
  if (distance >= 0 && distance <= 15) {
    if (currentMillis - previousMillis1 >= interval1) {
      previousMillis1 = currentMillis; // Save the last time the LED was toggled
      digitalWrite(ledPin1, !digitalRead(ledPin1)); // Toggle LED1
    }
  } else {
    digitalWrite(ledPin1, LOW); // Ensure LED1 is off if distance is not in range 0-15 cm
  }

  // Control LED2 based on distance range 16-30 cm
  if (distance >= 16 && distance <= 30) {
    if (currentMillis - previousMillis2 >= interval2) {
      previousMillis2 = currentMillis; // Save the last time the LED was toggled
      digitalWrite(ledPin2, !digitalRead(ledPin2)); // Toggle LED2
    }
  } else {
    digitalWrite(ledPin2, LOW); // Ensure LED2 is off if distance is not in range 16-30 cm
  }

  // Control LED3 based on distance range 31-45 cm
  if (distance >= 31 && distance <= 45) {
    if (currentMillis - previousMillis3 >= interval3) {
      previousMillis3 = currentMillis; // Save the last time the LED was toggled
      digitalWrite(ledPin3, !digitalRead(ledPin3)); // Toggle LED3
    }
  } else {
    digitalWrite(ledPin3, LOW); // Ensure LED3 is off if distance is not in range 31-45 cm
  }

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(50); // Short delay for stability
}
