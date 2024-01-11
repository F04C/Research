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
}

void loop() {
  // Display each LED in the matrix
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      lc.setLed(0, row, col, true);  // Turn on the current LED
      delay(100);                   // Wait for 100 milliseconds
      lc.setLed(0, row, col, false); // Turn off the current LED
    }
  }

  delay(1000);  // Wait for 1 second before repeating the pattern
}
