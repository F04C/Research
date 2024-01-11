#include <LedControl.h>

// Define the MAX7219 module connections
#define DIN_PIN 11
#define CS_PIN 10
#define CLK_PIN 13

// Create a LedControl object
LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);

void setup() {
  // Initialize the MAX7219 module
  lc.shutdown(0, false);      // Enable the display
  lc.setIntensity(0, 8);      // Set the brightness (0-15)
  lc.clearDisplay(0);         // Clear the display

  // Set digital pins as inputs for crack detection
  for (int row = 2; row < 4; row++) {
    pinMode(row, INPUT);
  }
  for (int col = 4; col < 6; col++) {
    pinMode(col, INPUT);
  }
}

void loop() {
  // Display a pattern on the 2x2 LED matrix
  for (int row = 0; row < 2; row++) {
    for (int col = 0; col < 2; col++) {
      // Check for cracks
      int rowCrack = digitalRead(2 + row);
      int colCrack = digitalRead(4 + col);

      if (rowCrack == HIGH || colCrack == HIGH) {
        Serial.println("Crack detected at Row: " + String(row) + ", Col: " + String(col));
        lc.setLed(0, row, col, true);  // Turn on LEDs in the cracked position
        // You can take further actions when a crack is detected
      } else {
        lc.setLed(0, row, col, false); // Turn off LEDs in the current row and column
      }
      delayMicroseconds(100);         // Adjust this delay for faster refresh rates (1000 microseconds = 1 millisecond)
    }
  }
}
