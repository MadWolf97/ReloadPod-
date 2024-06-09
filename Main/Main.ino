//LIBRARIES
#include <LiquidCrystal.h>
/*Will be implemented with TackNet
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
*/

//PIN ASIGMENTS MIGHT BE CHANGED LATER
  //Screen pins asignations
  LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
  
  /*Will be implemented with TackNet
  //Radio pins asignation
  RF24 radio(10, 9);               // nRF24L01 (CE,CSN)
  RF24Network network(radio);      // Include the radio in the network
  //Radio Buttons asignation
  const uint16_t this_node = 02;   // Address of our node in Octal format ( 04,031, etc)
  const uint16_t master00 = 00;    // Address of the other node in Octal format
  //Radio variable inicialization
  const unsigned long interval = 10;  //ms  // How often to send data to the other unit
  unsigned long last_sent;            // When did we last send?
  */
  
  //Buttons pins asignations
  const int emptyBoxPin = 8;
  const int feedingButtonPin =14;
  const int bbSensorPin = 15;
  const int loadingModePin = 17;
  /* will be added with profiles implementation
  const int encoderUpPin = 
  const int encoderDownPin = 
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

  // INITIAL PROFILE PARAMETERS
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
    /*Will be implemented with TackNet
    SPI.begin();
    radio.begin();
    network.begin(90, this_node);  //(channel, node address)
    radio.setDataRate(RF24_2MBPS);
    */
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

//MAIN LOOP
void loop() {
  //LOOP VARIABLES INICIALIZATION
  bool lastAlert = false;
  bool lastRefill = false;

  //BUTTONS UPDATE
  buttonStateUpdate();
  
  //PROFILE AND TOKEN ADQUISITION
  /*Will be imlemented with TackNet
  token = tokenUpdate();
  */

  //Temporal try, will be deleted with Profiles implementation
  profileName = "PISTOLA  ";
  bbLimit = 14;
  tokenNeeded = 2;
  /*
  profileName = getProfileName();
  bbLimit = getbbLimit();
  tokenNeede = getTokenNeeded();
  */

  //MAIN PROGRAM
  while (emptyBoxState == LOW){
    emptyAlert();
    lastAlert = true;
  }

  //Only gets displayed if there was an empty box alert
  if (lastAlert == true){
    refillSuccess();
    delay (3000);
  }

  while (emptyBoxState == HIGH){
    buttonStateUpdate();
    infoDisplay();
    if (aviability == true){ 
      if (feedingButtonState == HIGH){
        lastRefill = true;
        bbCounter();
        feedCut();
      }
    }

    //Delay to see bbCount
    if (lastRefill == true){
      if (magLimitation == true){
        //Will be changed with TackNet
        token = token - tokenNeeded;      
        /*Will be implemented with TackNet
        tokenConsumption(token - tokenNeeded);
        */
      }
      if (magLimitation == false){
        /* This is only used for getting the statitics 
        needed for equilibrating future games */
        tokenCounter();
      }
      delay(3000);
      bbCount = 0;
    }
  }
  //Precaution if some of the cicles gets interrupted
  feedCut();
}

// Displays the basic information on screen
void infoDisplay(){
  //Printing first row, depends on inizialization mode: TackNet ON or OFF
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
  //Printing second row, will display profiles and bbLimitations
  lcd.setCursor(0, 1);
  lcd.print(profileName);
  lcd.setCursor(9, 1);
  lcd.print("  0");
  lcd.setCursor(12, 1);
  lcd.print("/" + numFormat(bbLimit));
}

// Empty deposit ALERT and REFILLING
void emptyAlert(){
  buttonStateUpdateAlert();
  lcd.setCursor(0, 0);
  lcd.print("DEPOSITO VACIO  ");
  lcd.setCursor(0, 1);
  lcd.print("DIAL + TUBO     ");
  // This ignores all bb Limitations
  while (feedingButtonState == HIGH && encoderDepressState == HIGH){
    feed();
    buttonStateUpdateReload();
  }
  feedCut();
}

//This informs that the refilling process was succesfull
void refillSuccess(){
  lcd.setCursor(0, 0);
  lcd.print("     RECARGA    ");
  lcd.setCursor(0, 1);
  lcd.print("   FINALIZADA   ");
}

//This method feeds bbs, counts and displays the bbs that have been feed
void bbCounter(){
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
      buttonStateUpdateReload(); 
  }
  feedCut();
}

//this method shows how many mags you can reload
int magCounter(){
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

/*Will be implemented with TackNet
//This method gets the information from the main unit
int tokenUpdate(){ 
  network.update();
  network.read(avaliableTokens); // Read the incoming data
  return avaliableTokens;
}

//This method comunicates the tokens consumed by the last refill to the main unit
void tokenConsumption (int token){
  network.update();
  unsigned long now = millis();
  if (now - last_sent >= interval) {   // If it's time to send a data, send it!
    last_sent = now;
    RF24NetworkHeader header(master00);   // (Address where the data is going)
    network.write(token); // Send the data
  }
}
*/

//THE FUNCTIONS BELOW ARE FOR CONVENIENCE
//This method actualices the button states only for emergency refill
void buttonStateUpdateAlert(){
  emptyBoxState = digitalRead(emptyBoxPin);
  feedingButtonState = digitalRead(feedingButtonPin);
  encoderDepressState = digitalRead(encoderDepressPin);
  //Other operational buttonState Override
  bbSensorState = 0;
  /*encoderUpState = 0;      
  encoderDownState = 0;
  */
}
//This method actualices ONLY the button states needed during refill
void buttonStateUpdateReload (){
  emptyBoxState = digitalRead(emptyBoxPin);
  feedingButtonState = digitalRead(feedingButtonPin);
  bbSensorState = digitalRead(bbSensorPin);
  //Other operational buttonState Override
  encoderDepressState = 0;
  /*encoderUpState = 0;      
  encoderDownState = 0;
  */
}

//This method actualices ALL the button states for regular operation
void buttonStateUpdate (){
  buttonStateUpdateReload ();
  /* will be added with profiles implementation
  encoderUpState = digitalRead(encoderUpPin);      
  encoderDownState = digitalRead(encoderDownPin);   
  */
}

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
