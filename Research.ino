#include <LedControl.h>
// Define the MAX7219 module connections
#define DIN_PIN 12
#define CS_PIN 10
#define CLK_PIN 13

#define ROW0 2
#define ROW1 3
#define ROW2 4
#define ROW3 5
#define ROW4 6
#define ROW5 7
#define ROW6 8
#define ROW7 9

#define COL0 22
#define COL1 24
#define COL2 26
#define COL3 28
#define COL4 30
#define COL5 32
#define COL6 34
#define COL7 36

// Define crack detection pins
#define ROW_START_PIN ROW0
#define COL_START_PIN COL0

// Create a LedControl object
LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);

void setup() 
{
  Serial.begin(9600); // Initialize Serial communication (for debugging purposes only)

  // Initialize the MAX7219 module
  lc.shutdown(0, false);      // Enable the display
  lc.setIntensity(0, 8);      // Set the brightness of the dotmatrix (15 is the highest)
  lc.clearDisplay(0);         // Clearing of the display
}

void loop() {
  // Check for cracks and display on the 8x8 LED matrix
  for (int row = 0; row < 8; row++) 
  {
    int rowCracked = digitalRead(ROW_START_PIN + row);
    for (int col = 0; col < 8; col++) 
    {
      int colCracked = digitalRead(COL_START_PIN + col);

      if (rowCracked == LOW || colCracked == LOW) {
        Serial.println("Crack detected at Row: " + String(row) + ", Col: " + String(col));
        lc.setLed(0, row, col, true);
      } else {
        lc.setLed(0, row, col, false);
      }
      //delay(2000);
      delayMicroseconds(1000);
    }
  }
  // Uncomment the line below if there's a need of a delay between cycles
  // delay(500);
}
