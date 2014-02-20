#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

//define how many stepper increments are in one inch.
#define STEPS_PER_INCH 505
//set password
#define PASSWORD 6175

#define TRUE 1
#define FALSE 0

// Define Global variables and definitions for program use
#define LOWBYTE 2
#define HIGHBYTE 3
//used to store and manipulate the inventory status.
unsigned int inventory; 



/* 
 * LCD RS pin to digital pin 11
 * LCD Enable pin to digital pin 10
 * LCD D4 pin to digital pin A3
 * LCD D5 pin to digital pin A2
 * LCD D6 pin to digital pin A1
 * LCD D7 pin to digital pin A0
 */
 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(11, 10, A3, A2, A1, A0);

// initialize the keypad 

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

// Connect keyboard to arduino pins.
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad

// Call keypad class
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
//  EEPROM.write(LOWBYTE, 255);
//  EEPROM.write(HIGHBYTE, 255);
  vendorInit();
  Serial.begin(115200);
  
}

void loop() {
  commandInput();
}
