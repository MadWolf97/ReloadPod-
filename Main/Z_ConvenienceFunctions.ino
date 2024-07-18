//THE FUNCTIONS IN THIS FILE ARE FOR CODE OVERVIEW SIMPLIFICATION

//INPUTS
//This method actualices the button states only for emergency refill
void buttonStateUpdateAlert(){
  emptyBoxState = digitalRead(emptyBoxPin);
  feedingButtonState = digitalRead(feedingButtonPin);
  encoderDepressState = digitalRead(encoderDepressPin);
}

//This method actualices ONLY the button states needed during refill
void buttonStateUpdateReload (){
  emptyBoxState = digitalRead(emptyBoxPin);
  feedingButtonState = digitalRead(feedingButtonPin);
  bbSensorState = digitalRead(bbSensorPin);
}

//This method actualices ALL the button states for regular operation
void buttonStateUpdate (){
  buttonStateUpdateReload ();
  encoderUp();
  encoderDown();
}

//Reads the encoder up movements
bool encoderUp(){
  encoderUpState = digitalRead(encoderUpPin);      
  if (encoderUpState != lastEncoderUpState && encoderUpState == HIGH){
    lastEncoderUpState = encoderUpState;
    return true;
    delay (200);
  }else {lastEncoderUpState = encoderUpState; return false;}
}

//Reads the encoder down movements
bool encoderDown(){
  encoderDownState = digitalRead(encoderDownPin); 
  if (encoderDownState != lastEncoderDownState && encoderDownState == HIGH){
    lastEncoderDownState = encoderDownState;
    return true;
    delay (200);
  }else {lastEncoderDownState = encoderDownState; return false;}
}

//OUTPUTS
//This method formats the numbers returned by counting methods
String numFormat (int number){
  if (number < 10){
    return "  " + (String) number;
  }
    if (10 <=number && number < 100){
    return " " + (String) number;
  }
  else{
    return (String) number;
  }
}

//This will feed bbs to your magazine
void feed() {
  digitalWrite(motor, HIGH); //spin motor
}

//This stops the motor
void feedCut(){
  digitalWrite(motor, LOW);
}
