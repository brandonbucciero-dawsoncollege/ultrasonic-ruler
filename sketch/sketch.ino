// Including libraries
#include <LiquidCrystal.h>
#include <NewPing.h>

#define TRIGGER_PIN 12    // HC-SR04 trigger pin
#define ECHO_PIN 11       // HC-SR04 echo pin
#define MAX_DISTANCE 400  // Max distance in cm to measure
#define BUTTON_PIN 4      // Button pin

bool metric;        // Make a boolean to select inches
bool last_state;    // For making button toggle
bool current_state; // Also for making button toggle

// Initializing LiquidCrystal object with pins (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(5, 6, 7, 8, 9, 10);

// Initializing NewPing object with the defined values
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  pinMode(BUTTON_PIN, INPUT); // Set button pin to input
  Serial.begin(9600);         // Start serial monitor
  metric = true;              // Set metric to true (use cm first)
  last_state = true;          // Start with last state being true (not pressed)
  current_state = true;       // Start with current state being true (not pressed)
  lcd.begin(16, 2);           // Start 16x2 LCD display
}

void loop() {
  int distance = sonar.ping();                  // New integer for distance in echo time in microseconds
  int distance_cm = sonar.convert_cm(distance); // New integer for distance in centimetres
  int distance_in = sonar.convert_in(distance); // New integer for distance in inches

  serialMonitor(distance_cm, distance_in);  // Calls serialMonitor() function
  lcdDisplay(distance_cm, distance_in);     // Calls lcdDisplay() function
  buttonToggling();                         // Calls buttonToggling() function
}

// Function which displays messages in the serial monitor
void serialMonitor(int cm, int in) {
  delay(50);  // Delay of 50 ms between loops
  Serial.print("Distance: ");
  // Checking to display in centimetres or in inches
  if (metric == true) {
    Serial.print(cm);
    Serial.println(" cm");
  } else {
    Serial.print(in);
    Serial.println(" in");
  }
}

// Controls the LCD display
void lcdDisplay(int cm, int in) {
  delay(50);              // Delay of 50 ms between loops
  lcd.clear();            // Clears the display between loops
  lcd.print("Distance:");
  lcd.setCursor(0, 1);    // Sets cursor to second line
  // Checking to display in centimetres or in inches
  if (metric == true) {
    lcd.print(cm);
    lcd.print(" cm");
  } else {
    lcd.print(in);
    lcd.print(" in");
  }
}

// Make the button toggle the metric boolean
void buttonToggling() {
  current_state = digitalRead(BUTTON_PIN);  // Current state of the button
  // Checking if current state is 0 (pushed) and previous was 1 (not pushed)
  if (current_state == 0 && last_state == 1) {
    metric = !metric; // Setting metric to whatever it was not previously (0 -> 1, 1 -> 0)
  }
  last_state = current_state; // Changing the last state to the current state after the previous steps
}
