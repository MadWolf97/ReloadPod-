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
  const int radioSwitchPin = 18;

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
  int bbCount = 0;
  String profileName;
  int bbLimit;
  int tokenNeeded;
  int token = 0;
  bool magLimitation;
  bool aviability;

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

//THIS LOADS ALL SETTINGS AND MESAGES BEFORE GAME USEAGE
void setup() {
  //test
  token = 10;

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

  //PreGame settings check
  radioSwitchState = digitalRead(radioSwitchPin);
  loadingModeState = digitalRead(loadingModePin);

  //Independent mode: TackNet OF
  if (radioSwitchState == LOW){
    magLimitation = false;
    lcd.setCursor(0, 0);
    lcd.print("MODO DE CONTROL");
    lcd.setCursor(0, 1);
    lcd.print("INDEPENDIENTE");
    delay(1000);
  }

  //Slaved mode: TacNet ON
  else{
    magLimitation = true;
    lcd.setCursor(0, 0);
    lcd.print("MODO DE CONTROL");
    lcd.setCursor(0, 1);
    lcd.print("ESCLAVIZADO");
    delay(1000);
  }

  /*this will be added with profiles
  if (loadingModeState == HIGH){
    profiles limited: REAL CAP
  }
  else{
    profiles complete
  }
  */
}

//This function actualices ONLY the button states needed during refill
void buttonStateUpdateReduced (){
  emptyBoxState = digitalRead(emptyBoxPin);
  feedingButtonState = digitalRead(feedingButtonPin);
  bbSensorState = digitalRead(bbSensorPin);
}

//This function actualices ALL the button states for regular operation
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

  //PROFILE AND TOKEN ADQUISITION
  //Temporal try, will be deleted with Profiles implementation
  profileName = "PISTOLA  ";
  bbLimit = 14;
  tokenNeeded = 2;


  //MAIN PROGRAM
  if(emptyBoxState == LOW){
    emptyAlert();
  }

  else {
    bbCount = 0;
    info();
    if (aviability == true){ 
      if (feedingButtonState == HIGH){
        if (magLimitation == true){
          token = token - tokenNeeded;      
          /*
          TackNet comunication will be added latter
          */
        }
          if (magLimitation == false){
          tokenCounter();
        }
        bbCounter();
        feedCut();
        //Delay in order to see the bbCount
        delay(2000);
      }
    }
  }
  //Precaution if some of the cicles gets interrupted
  feedCut();
}

// Displays the basic information on screen
void info(){
  lcd.setCursor(0, 0);
  if (magLimitation == true){
    lcd.print("MAGS LEFT    ");
    lcd.setCursor(13, 0);
    lcd.print(numFormat(magCounter()));
  }
  else{
    lcd.print("TOKENS USED  ");
    lcd.setCursor(13, 0);
    lcd.print(numFormat(token));
    aviability = true;
  }
  lcd.setCursor(0, 1);
  lcd.print(profileName);
  lcd.setCursor(9, 1);
  lcd.print("  0");
  lcd.setCursor(12, 1);
  lcd.print("/" + numFormat(bbLimit));
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
    buttonStateUpdateReduced();
  }
  feedCut();
}

//This method feeds bbs, counts and displays the bbs that have been feed
void bbCounter (){
  //Only counts the times the sensor has gone from OFF to ON
  while (bbCount < bbLimit && feedingButtonState == HIGH && emptyBoxState == HIGH){
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
    lcd.print(numFormat(bbCount));
    buttonStateUpdateReduced(); 
  }
  feedCut();
}

//this method shows how many mags you can reload
int magCounter (){
  int mags = token / tokenNeeded;
  if (mags > 0){
      aviability = true;
    }
    else{
      aviability = false;
    }
  return mags;
}

//This method counts the amount of tokens it would have consumed during the game
int tokenCounter(){
  token = token + tokenNeeded;
  return token;
}

//THE FUNCTIONS BELOW ARE FOR CONVENIENCE
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
