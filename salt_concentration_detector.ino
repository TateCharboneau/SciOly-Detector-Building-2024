#include <LiquidCrystal.h>

// LCD Initialization
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Variable Instantiation:
const int blueLED = 8; // Output Pin for Blue LED
const int greenLED = 9; // Output Pin for Green LED
const int redLED = 10; // Output Pin for Red LED
const double wPin = 0; // Input Pin for Water Voltage
float wInput; // Number Input from Water Voltage (From 0 - 1000)
float wVoltage; // Voltage Reading for Water
float wmVoltage; // mV Reading for Water
int ppm = 0; // PPM Reading
const float vConversion = .00107421875; // Variable for converting analog wInput to voltage
const float a = 2140.072; // Variable for Exponential Equation (y = a * b^x )
const float b = .3018; // Variable for Exponential Equation (y = a * b^x)

// Setup
void setup() {

  lcd.begin(16, 2); // Sets and begins LCD screen with 16 columns and 2 rows
  // Setting Pin Mode for Pins:
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(wPin, INPUT);
  analogReference(INTERNAL);

}

void loop() {

  wInput = analogRead(wPin); // Reads the input from the water voltage

// Voltage Calculation
  wVoltage = (591 - wInput) * vConversion;
  wmVoltage = wVoltage * 1000;

// PPM Calculation
  ppm = .0000000012165863586338 * pow(1.3526742084485, wmVoltage);


// Displays Mass and Voltage
if (ppm > 300) {
  lcd.print("PPM: ");
    lcd.setCursor(5, 0);
    lcd.print("           ");        
    lcd.setCursor(5, 0);
    lcd.setCursor(5, 0);
    lcd.print(ppm);
    lcd.print("PPM");
  
  lcd.setCursor(0, 1);
  lcd.print("Voltage: ");
  lcd.print(wVoltage);
  lcd.print("V");
  lcd.setCursor(0, 0);


// LED Functionality
  // Blue LED
  if ((0 <= ppm) && (ppm <= 2000)) {
    digitalWrite(blueLED, HIGH);
  }
  else {
    digitalWrite(blueLED, LOW);
  }
  
  // Green LED
  if ((2000 < ppm) && (ppm <= 3500)) {
    digitalWrite(greenLED, HIGH);
  }
  else {
    digitalWrite(greenLED, LOW);
  }

  // Red LED
  if ((3000 < ppm) && (ppm <= 5000)) {
    digitalWrite(redLED, HIGH);
  }
  else {
    digitalWrite(redLED, LOW);
  }
}

}
