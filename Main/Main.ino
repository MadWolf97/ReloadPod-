#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

//PIN ASIGMENTS MIGHT BE CHANGED LATER
  //Buttons pins asignations
  const int emptyBoxPin = 8;
  const int feedingButtonPin =14;
  const int bbSensorPin = 15;
  const int loadingModePin = 17;
  /* will be added with profiles implementation
  const int encoderUpPin
  const int encoderDownPin
  */
  const int encoderDepressPin = 16;
  const int radioSwitchPin = 19;

  //Actuators pin asigments
  const int motor = 19;


//GOLBAL VARIABLE INITIALLIZATION
  //Variables reading set up
  int emptyBoxState = 0;
  int feedingButtonState = 0;
  int bbSensorState = 0;
  int loadingModeState = 0;
  /* will be added with profiles implementation
  int encoderUpState = 0;
  int encoderDownState = 0;
  */
  int encoderDepressState = 0;
  int radioSwitchState = 0;

  //Utility variables
  int lastbbSensorState = 0;

  // INITIAL PARAMETERS
  //Preset Profiles   (profileName, bbLimit, tokenNeeded)
  /*
  ("Pistola",14,1);
  ("Franco",10,3);
  ("Selecto",20,3);
  ("Asalto",30,3);
  ("Apollo",180,5);


  ("LowCap",90);
  ("MidCap",120);
  ("MidCap",160);
  */

  //Temporal try, will be deleted with Profiles implementation
  String profileName;
  int bbLimit;
  int tokenNeeded;
  int token;


//THIS LOADS ALL SETTINGS AND MESAGES BEFORE GAME USEAGE
void setup() {
   // Button input/output set
  pinMode(emptyBoxPin, INPUT);
  pinMode(feedingButtonPin, INPUT);
  pinMode(bbSensorPin, INPUT);
  pinMode(loadingModePin, INPUT);
  /* will be added with profiles implementation
  pinMode(encoderUpPin, INPUT);
  pinMode(encoderDownPin, INPUT);
  */
  pinMode(encoderDepressPin, INPUT);
  pinMode(radioSwitchPin, INPUT);

  //Actuators
  pinMode(motor, OUTPUT);

  // LCD sizing
  lcd.begin(16, 2);

  //Activation message
  lcd.setCursor(0, 0);
  lcd.print("ACTIVADO");
  delay(1000); 

  void initialSettings(){
    //PreGame settings check
    loadingModeState = digitalRead(loadingModePin);
    radioSwitchState = digitalRead(radioSwitchPin);

    //Independent mode: TackNet OF
    if (radioSwitchState == LOW){
      lcd.setCursor(0, 0);
      lcd.print("MODO DE CONTROL");
      lcd.setCursor(0, 1);
      lcd.print("INDEPENDIENTE");
      delay(1000);
    }

    //Slaved mode: TacNet ON
    /* WILL BE IMPLEMENTED AT THE END
    else{
      lcd.setCursor(0, 0);
      lcd.print("MODO DE CONTROL");
      lcd.setCursor(0, 1);
      lcd.print("ESCLAVIZADO");
      delay(1000);
    }
    */

  /*this will be added with profiles
    if (loadingModeState == HIGH){
      profiles limited
    }
    else{
      profiles complete
    }
    */
  }
}

//This function actualices ONLI the button states needed during refill
void buttonStateUpdateReduced (){
  emptyBoxState = digitalRead(emptyBoxPin);
  feedingButtonState = digitalRead(feedingButtonPin);
  bbSensorState = digitalRead(bbSensorPin);
}

//This function actualices ALL the button states for operation
void buttonStateUpdate (){
  buttonStateUpdateReduced ();
  /* will be added with profiles implementation
  encoderUpState = digitalRead(encoderUpPin);      
  encoderDownState = digitalRead(encoderDownPin);   
  */
  encoderDepressState = digitalRead(encoderDepressPin);
}

//MAIN LOOP
void loop() {
  buttonStateUpdate();

  //Profile and token information adquisition
  //Temporal try, will be deleted with Profiles implementation
  profileName = "PISTOLA     ";
  bbLimit = 14;
  tokenNeeded = 1;
  token = -1;

  //MAIN PROGRAM
  if(emptyBoxState == LOW){
    emptyAlert();
  }

  if (emptyBoxState == HIGH && feedingButtonState == LOW){
    info(profileName, bbLimit, tokenNeeded, token);
  }

  while (emptyBoxState == HIGH && feedingButtonState == HIGH){ //&& avialbility = true // will add with TackNet
    bbCounter(bbLimit);
    feedCut();
    //Delay in order to see the bbCount
    delay(3000); 
  }
}

// Displays the basic information on screen
void info(String profileName, int bbLimit, int tokenNeeded, int token){
  lcd.setCursor(0, 0);
  lcd.print("MAGS LEFT    ");
  lcd.setCursor(13, 0);
  magCounter(token, tokenNeeded);
  lcd.setCursor(0, 1);
  lcd.print(profileName);
  lcd.setCursor(12, 1);
  lcd.print("/" + (String) bbLimit);
}

// Empty deposit ALERT and REFILLING
void emptyAlert(){
  lcd.setCursor(0, 0);
  lcd.print("DEPOSITO VACIO  ");
  lcd.setCursor(0, 1);
  lcd.print("DIAL + TUBO     ");
  // This ignores all bb Limitations
  while (feedingButtonState == HIGH && encoderDepressState == HIGH){
    feed();
  }
  feedCut();
}

//This method feeds bbs, counts and displays the bbs that have been feed
String bbCounter (int bbLimit){
  //Only counts the times the sensor has gone from of to on
  int bbCount = 0;
  // int bbLimit = 30; //will be changed later with profile implementation
  while (bbCount <= bbLimit){
    feed();
    if (lastbbSensorState != bbSensorState){
      if (bbSensorState == HIGH){
        bbCount++;
        lastbbSensorState = bbSensorState;
      }
      else{
        lastbbSensorState = bbSensorState;
      }
    }
    lcd.setCursor(9,1);
    return (String) bbCount;
  }
}

//this method shows how many mags you can reload
void magCounter (int token, int tokenNeeded){
  if (token<=-1){
    lcd.setCursor(13, 0);
    lcd.print("INF");
    //aviability = true;
  }
  else{
    int mags = token / tokenNeeded;
    lcd.setCursor(13, 0);
    lcd.print(mags);
    //aviability = true;
    /*  will be implemented with TackNet
    if (mags < 0){
      aviability = true;
    }
    else{
      aviability = false;
    }
    */
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
