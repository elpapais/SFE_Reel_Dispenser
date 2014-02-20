// Functions and routines

unsigned int getInventory(void){
  
  unsigned int _inventory = 0;
  //Read bytes from EEPROM into temporary variables
  unsigned char byte0 = EEPROM.read(LOWBYTE); //pull data from the EEPROM @ address 0x00  
  unsigned char byte1 = EEPROM.read(HIGHBYTE); //pull data from the EEPROM @ address 0x01
  
  //Pack all the pieces into the inventory value.
  _inventory |= byte1 << 8;
  _inventory |= byte0;
  
  return _inventory;  //return inventory level
}

void setInventory(unsigned int _inventory){

  //Unpack bytes from inventory and prepare for EEPROM storage

  unsigned char byte0 = (_inventory);
  unsigned char byte1 = (_inventory >> 8);
  
  //Write bytes to EEPROM for non-volatile storage
  EEPROM.write(LOWBYTE, byte0);
  EEPROM.write(HIGHBYTE, byte1);

}

// Initalize vendor and setup for use
void vendorInit(void){
   // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Show splash screen
  lcd.print("Vendomatic");
  
  pinMode(12, OUTPUT);  //Stepper - STEP
  pinMode(13, OUTPUT);  //Stepper - DIR 
  pinMode(9, OUTPUT); //Stepper - ENABLE
  digitalWrite(13, HIGH);
  digitalWrite(9, HIGH); //DISABLE STEPPER.
  // set motor relay pin to output
  pinMode(A4, OUTPUT);
  // set motor relay output to low to ensure motor will not move.
  digitalWrite(A4, LOW);
  // set motor sensor pin to input
  pinMode(A5, INPUT);
  //laod current inventory into volotale memory.
  inventory = getInventory();
  delay(100);
}

void commandInput(){
  //Display prompt to enter requested length in feet.
  lcd.clear();
  lcd.print("Enter(ft)");
  lcd.setCursor(0,1);
  lcd.print(inventory); 
  lcd.print(" - Remain");
  
  //create a varialbe to store key input
  char key = 0;
  //wait for a key to be pressed
  //While waiting for a key scroll the menu
  while(key == NO_KEY){
    for(int i = 0; i < 15; i++){
      key = keypad.getKey();
      if(key != NO_KEY) break;
      delay(10);
    }
    //Not needed anymore lcd.scrollDisplayLeft(); 
  }
  //when a key is pressed reset the display 
  lcd.clear();
  lcd.print("Enter(ft)");
 
  //create an array to store key presses  
  char data[10] = {0,0,0,0,0,0,0,0,0,0};
  //only collect a maximum of 10 keys
  for(int i = 0; i <= 10; i++){
    Serial.print("key ");
    Serial.println(i);
    if(key == '*'){

     //menue or escape option 
     //if the index is still 0 (meaning no keys have been 
     //pressed) jump to the menu selection.
     if(i <= 0){
       char test = enter_password();
       if(test == TRUE) selectionMenu();
       break;
     }
     //if there are any keys other than '*' in the data[] 
     //array use this as an escape key to quit.
     if(i >= 1){
       lcd.clear();
       lcd.print("EJECT EJECT!!");
       delay(750); 
       break;
     }
    }
    if(key == '#'){
      //enter button
      //If no value set report error and break
      if(i == 0){
        lcd.clear();
        lcd.print("No Value");
        delay(500);
        break;
      }
     
     //Turn the string into a variable for output
      int vendValue;
      vendValue = atoi(data);
      //check to make sure there is enough inventory to vend
      if(vendValue > inventory){
        lcd.clear();
        lcd.print("Not Enough Material!");
        lcd.setCursor(0,1);
        lcd.print(vendValue - inventory);
        lcd.print(" required");
        delay(1000);
        //if there is not enough inventory break and skip the vend
        break;
      }
      //check to see if requested vend is 0
      if(vendValue == 0){
        lcd.clear();
        lcd.print("Cannot vend zero!");
        lcd.setCursor(0,1);
        lcd.print("... Really?");
        delay(1000);
        break;  
      }
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Are you sure?");
      lcd.setCursor(0,1);
      lcd.print("* to bail");
      delay(500);
      int z;
      char input;
        for(z = 0; z < 1000; z++){
        //Check the keypad for a key entry
         input = keypad.getKey();
        //When a key is pressed exit the loop.
        if(input != NO_KEY) break;
        delay(10);
        }
      if(z >= 1000) break; //Timedout
      if(input != '#') break; // Only accept enter key.
      
      
      //if all checks out vend material
      Serial.println(vendValue);
      vend(vendValue);
      break;
    }
    //if "key" is not an action key, NOW put it in the array.
    //the order of this is important to keep "action keys" out of the array.
    data[i] = key;
    lcd.setCursor(i, 1);
    lcd.print(key);
    //wait for the next key to be pressed.  This entire loop will execute a maximum
    //of 10 times to limit the input.  
    key = keypad.getKey(); //Check for new key.
    
    int n = 0; //creat "n" outside the loop so we can use it later to determine if
           //there was a timeout.
    while(key == NO_KEY){
      //check and wait for more keys.
      //The loop is designed to give a timeout period
      //The timeout is adjusted by the number of loops with the delay(10);
      //If a longer timeout is desired, increase the loop count rather than the 
      //delay.  Increasing the delay will affect the accuracy of picking up a key
      //press. The current time out is 1s
      for(n = 0; n < 1000; n++){
        //Check the keypad for a key entry
        key = keypad.getKey();
        //When a key is pressed exit the loop.
        if(key != NO_KEY) break;
        delay(10);
      }
      //Check to see if a key was pressed OR if a timeout occured.
      if(n >= 1000){
        //a timeout was reached, bail out
        break;
      } 
    } 
    //check for timeout or error
      if(n >= 1000){
        //a timeout was reached
        lcd.clear();
        lcd.print("TIMEOUT!");
        lcd.setCursor(0,1);
        lcd.print("Slopoke!");
        delay(500);
        break;
      }
    //TODO: FIND MORE ERROR CODES
      
  }  
}
