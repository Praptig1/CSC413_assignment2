#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD setup (address 0x27 is common, adjust if different)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Button and LED pin definitions
const int buttonPins[6] = {A0, A1, A2, A3, A4, A5}; // Analog pins for buttons
const int ledPins[10] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12};          // Pins for LED bar graph levels

void setup() {
  // Initialize LCD
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();
  
  // Initialize button pins as input with pull-up resistors
  for (int i = 0; i < 6; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  // Initialize LED pins as output
  for (int i = 0; i < 10; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // Initial LCD message
  lcd.setCursor(0, 0);
  lcd.print("Total: 776.62m");
}

void loop() {
  for (int i = 0; i < 6; i++) {
    // Check if button is pressed (LOW because of pull-up resistor)
    if (digitalRead(buttonPins[i]) == LOW) {
      handleButtonPress(i);
      delay(300); // Debounce delay
    }
  }
}

// Function to handle button press actions
void handleButtonPress(int buttonIndex) {
  // Clear previous display and move cursor to the beginning
  lcd.clear();
  lcd.setCursor(0, 0);

  // Set LCD message and LED bar level based on button pressed
  switch (buttonIndex) {
    case 0:
    //NA
      lcd.print("124.5mil");
      setLEDBarLevel(5);
      break;
    case 1:
      lcd.print("15.01m");
      //Oceania
      setLEDBarLevel(1);
      break;
    case 2:
    //SA
      lcd.print("68.82m");
      setLEDBarLevel(3); 
      break;
    case 3:
    //Asia
      lcd.print("301.52m");
      setLEDBarLevel(10); 
      break;
    case 4:
    //Africa
      lcd.print("13.15m");
      setLEDBarLevel(1);
      break;
    case 5:
    //Europe
      lcd.print("253.62m");
      setLEDBarLevel(8);
      break;
  }
}

// Function to set LED bar graph level
void setLEDBarLevel(int level) {
  // Turn off all LEDs first
  for (int i = 0; i < 10; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  
  // Turn on LEDs up to the specified level
  for (int i = 0; i < level; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
}
