void selectionMenu(){
  lcd.clear();
  lcd.print("Menu");
  lcd.setCursor(0,1);
  lcd.print("1-Set inventory");
  char key = keypad.getKey(); //Check for new key.
    
  int n; //creat "n" outside the loop so we can use it later to determine if
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
      delay(5);
    }
    //Check to see if a key was pressed OR if a timeout occured.
    if(n >= 200){
      //a timeout was reached
      break;
    } 
  } 
  if(key == '1'){
    lcd.clear();
    lcd.print("Enter Inventory");
    //get input from keyboard
    key = keypad.getKey();
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
        delay(5);
      }
      //Check to see if a key was pressed OR if a timeout occured.
      if(n >= 200)break;
    }
    
    char data[10] = {0,0,0,0,0,0,0,0,0,0};
    //only collect a maximum of 10 keys    
    for(int i = 0; i <= 10; i++){
      if(key == '*') 
        break;
      if(key == '#'){
        if(i == 0){
          lcd.clear();
          lcd.print("No Value");
          delay(500);
          break;
        }
        //enter button
        //Turn the string into a variable for output
        unsigned int inventoryValue = atoi(data);
        Serial.print("inventory size = ");
        Serial.println(inventoryValue);

        //Set inventory
        setInventory(inventoryValue);
        inventory = getInventory();
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
          delay(5);
        }
        //Check to see if a key was pressed OR if a timeout occured.
        if(n >= 1000)break;
      } 
      //check for timeout or error
      if(n >= 200){
        //a timeout was reached
        lcd.clear();
        lcd.print("TIMEOUT!");
        lcd.setCursor(0,1);
        lcd.print("Slopoke!");
        delay(500);
        break;
      }
    }  
  }
  lcd.clear();
  lcd.print("Exiting");
  delay(750);
};

