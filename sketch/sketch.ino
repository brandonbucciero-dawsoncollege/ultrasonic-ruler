// Including libraries
#include <NewPing.h>

#define TRIGGER_PIN 12    // HC-SR04 trigger pin
#define ECHO_PIN 11       // HC-SR04 echo pin
#define MAX_DISTANCE 400  // Max distance in cm to measure

// Initializing NewPing object with the defined values
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);   // Start serial monitor
  bool inches = false;  // Make a boolean to select inches
}

void loop() {
  float distance_cm = sonar.ping_cm();      // New float for distance in centimetres
  float distance_in = sonar.ping_in();      // New float for distance in inches

  serialMonitor(distance_cm, distance_in);  // Calls serialMonitor() function
}

// Function which displays messages in the serial monitor
void serialMonitor(float cm, float in) {
  delay(50);                    // Delay of 50 ms between loops
  Serial.println("Distance: ");
  // Checking to display in centimetres or in inches
  if (in == false) {
    Serial.print(cm);
    Serial.print(" cm");
  } else {
    Serial.print(in);
    Serial.print(" in");
  }
}
