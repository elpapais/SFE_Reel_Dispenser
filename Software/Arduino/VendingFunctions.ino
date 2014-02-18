//Functions related to vending only

void vend(int vendLength){
  //vend material
    digitalWrite(9, LOW); //ENABLE STEPPER.
    delay(10);
    for(int a = 0; a < vendLength; a++)
    {
      for(int b = 0; b < 12; b++)
      {
        for(int c = 0; c < STEPS_PER_INCH; c++)
        {
          digitalWrite(12, HIGH);
          delayMicroseconds(150);
          digitalWrite(12, LOW);
          delayMicroseconds(150);
        }
      }
    }
    digitalWrite(9, HIGH); //DISABLE STEPPER.

  //update the material left in the device
  inventory = inventory - vendLength;
  setInventory(inventory);
  
  cutMaterial(); 
}

void cutMaterial(){
  //Cut material function
  //Run the cut motor with a maximum time limit.
  digitalWrite(A4, HIGH);
  //Give a minimum time to prevent a false positive on the limit switch
  delay(100);  
  //If the complete sensor is triggered the loop will break early
  for(int n = 0; n <= 1000; n++){
    if(digitalRead(A5) == 0)break;
    delay(5);  
  }
  digitalWrite(A4, LOW);
}
