/**
 * @author MadWolf97
 * @brief This is a loong term project to create a net of units 
 * that will be used to manage the munition resources for a airsoft game 
 * in various different modes
 * @version 0.9.4
 * 
 */

//LIBRARIES
#include <LiquidCrystal_I2C.h>

/*Will be implemented with TackNet
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
*/

//PIN ASIGMENTS MIGHT BE CHANGED LATER
  //Screen definition
  LiquidCrystal_I2C lcd(0x27,  16, 2);

  /*Will be implemented with TackNet
  //Radio pins asignation
  RF24 radio(10, 9);               // nRF24L01 (CE,CSN)
  RF24Network network(radio);      // Include the radio in the network
  //Radio Buttons asignation
  const uint16_t this_node = 01;   // Address of our node in Octal format ( 04,031, etc)
  const uint16_t master00 = 00;    // Address of the other node in Octal format
  //Radio variable inicialization
  const unsigned long interval = 10;  //ms  // How often to send data to the other unit
  unsigned long last_sent;            // When did we last send?
  */
  
  //Buttons pins asignations
  #define emptyBoxPin 15
  #define feedingButtonPin 16
  #define bbSensorPin 17
  #define loadingModePin 3
  #define encoderUpPin 5
  #define encoderDownPin 6
  #define encoderDepressPin 7
  #define radioSwitchPin 2
  #define startUpMenuButtonPin 4

  //Actuators pin asigments
  #define motor 19

//GOLBAL VARIABLE INITIALLIZATION
  //Variables reading set up
  int emptyBoxState = 0;
  int feedingButtonState = 0;
  int bbSensorState = 0;
  int loadingModeState = 0;
  int encoderUpState = 0;
  int encoderDownState = 0;
  int encoderDepressState = 0;
  int radioSwitchState = 0;
  int startUpMenuButtonState = 0;

  //Utility variables
  int lastbbSensorState = 0;
  int lastEncoderUpState = 0;
  int lastEncoderDownState = 0;
  int selectionFase = 0;
  int bbCount = 0;
  String profileName;   //Given by active profile
  int bbLimit;          //Given by active profile
  int tokenNeeded;      //Given by active profile
  int i = 0;            //Used to select active Profile
  int token = 0;        //Used for magCounter and TackNet
  bool aviability;      //Used to limit the acces to magazines when using TackNet
  

  //CLASS DEFINITION 
  /*
  will be refractored in to a header and a source file at some point
  */
  class Profile {
    public:
      Profile(String profileName, int bbLimit, int tokenNeeded);
      String profileName;
      int bbLimit;
      int tokenNeeded;

      //GETTERS
      String getProfileName();
      int getbbLimit();

      int getTokenNeeded();
      
      //SETTERS
      int setbbLimit();
      /*
      int settokenNeeded();
      */

    private:
        String _profileName;
        int _bbLimit;
        int _tokenNeeded;
  };

  //CONSTRUCTOR
  Profile::Profile(String profileName, int bbLimit, int tokenNeeded){
    String _profileName = profileName;
    int _bbLimit = bbLimit;
    int _tokenNeeded = tokenNeeded;
  };


  //GETTERS
  String Profile::getProfileName(){ 
    return _profileName; 
  };
  int Profile::getbbLimit(){ 
    return _bbLimit; 
  };

  int Profile::getTokenNeeded(){ 
    return _tokenNeeded; 
  };
  /*
  //SETTERS
  int Profile::setbbLimit(int bbLimit){ 
    _bbLimit = bbLimit; 
  };

  int Profile::settokenNeeded(int tokenNeeded){ 
    _tokenNeeded = tokenNeeded; 
  };*/

  // INITIAL PROFILE PARAMETERS
    //Preset Profiles   (profileName, bbLimit, tokenNeeded)
      Profile p1 ("PISTOLA   ",14,1);
      Profile p2 ("FRANCO    ",10,3);
      Profile p3 ("SELECTO   ",20,3);
      Profile p4 ("ASALTO    ",30,3);
      Profile p5 ("APOYO     ",180,5);

      Profile p6 ("LowCap    ",90,10);
      Profile p7 ("MidCap    ",120,14);
      Profile p8 ("MidCap    ",160,19);


//THIS LOADS ALL SETTINGS AND MESAGES BEFORE GAME USEAGE
void setup() {
  // Button input/output set
  pinMode(emptyBoxPin, INPUT);
  pinMode(feedingButtonPin, INPUT);
  pinMode(bbSensorPin, INPUT);
  pinMode(loadingModePin, INPUT);
  pinMode(encoderUpPin, INPUT);
  pinMode(encoderDownPin, INPUT);
  pinMode(encoderDepressPin, INPUT);
  pinMode(radioSwitchPin, INPUT);
  pinMode(startUpMenuButtonPin, INPUT);
  pinMode(startUpMenuButtonPin, INPUT);

  //Actuators
  pinMode(motor, OUTPUT);

  // LCD sizing
  lcd.begin(16, 2);
  lcd.backlight();

  //Activation message
  lcd.setCursor(0, 0);
  lcd.print("ACTIVADO");
  delay(1000); 

  //PreGame settings check
  radioSwitchState = digitalRead(radioSwitchPin);
  loadingModeState = digitalRead(loadingModePin);
  startUpMenuButtonState = digitalRead(startUpMenuButtonPin);
  startUpMenuButtonState = digitalRead(startUpMenuButtonPin);

  //Independent mode: TackNet OF
  if (radioSwitchState == LOW){
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
    lcd.setCursor(0, 0);
    lcd.print("MODO DE CONTROL");
    lcd.setCursor(0, 1);
    lcd.print("ESCLAVIZADO");
    delay(1000);
  }

  //This decides wich profiles will be avaliable during the game
  if (loadingModeState == HIGH){
    Profile *profileArray [5] = {&p1, &p2, &p3, &p4, &p5};
  }
  else{
    Profile *profileArray [8] = {&p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8};
  }
}

//MAIN LOOP
void loop() {
  //LOOP VARIABLES INICIALIZATION
  bool lastAlert = false;
  bool lastRefill = false;

  //BUTTONS UPDATE
  buttonStateUpdate();
  
  //TOKEN ADQUISITION
  /*Will be imlemented with TackNet
  token = tokenUpdate();
  */

  //profileManager();

  //Temporal try, will be deleted with Profiles implementation
  profileName = p2.getProfileName();
  bbLimit = p2.getbbLimit();
  tokenNeeded = p2.getTokenNeeded();


  //MAIN PROGRAM
  while (emptyBoxState == LOW){
    buttonStateUpdateAlert();
    emptyAlert();
    lastAlert = true;
  }

  //Only gets displayed if there was an empty box alert
  if (lastAlert == true){
    refillSuccess();
    delay (3000);
  }

  if (emptyBoxState == HIGH){
    buttonStateUpdate();
    //profileManager();
    infoDisplay();
    if (aviability == true){ 
      if (feedingButtonState == HIGH){
        lastRefill = true;
        bbFeeder();
        feedCut();
      }
    }

    //Token management
    if (lastRefill == true){
      tokenManager();
      delay(3000);    //Delay to see bbCount
      bbCount = 0;
    }
  }
  //Precaution if some of the cicles gets interrupted
  feedCut();
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
    buttonStateUpdateAlert();
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
/*
//This method controls the profiles
void profileManager(){
  if (encoderUpState == HIGH){
    i++;
    if (i >= profileArray.length()){  //Loops to first profile
      i = 0;
    }
    delay(500);
  }
  if (encoderDownState == HIGH){      
    i--;
    if (i < 0){                       //Loops to last profile
      i = profileArray.length();
    }
    delay(500);
  }

  //Info about profile update
  profileName::profileArray[i] -> getProfileName();
  bbLimit::profileArray[i] -> getbbLimit();
  tokenNeeded::profileArray[i] -> getTokenNeeded();
*/
/*
  //Profile modification. Only avaliable if mag limitations are not present
  if (encoderDepressState == HIGH && loadingModeState == LOW){
    delay(500);
    while(encoderDepressState == LOW){
      buttonStateUpdate();
      changebbLimit();
    }
  }
}
*/

/*
//This method lets us change the magazine capacity
void bbChanger(){
  lcd.setCursor(12, 1);
  lcd.print("/   ");
  delay(200);
  if (encoderUpState == HIGH){
    bbLimit++;
  }
  if (encoderDownState == HIGH && bbLimit < 0){
    bbLimit--;
  }
  profileArray[i] -> setbbLimit(bbLimit);
  lcd.setCursor(12, 1);
  lcd.print("/" + numFormat(bbLimit));
  delay(200);
}*/

//This method is used to change the default bbLimit and tokenNeeded for profiles during starup procedure
void startMenu(){
  lcd.setCursor(0, 0);
  lcd.print(profileName);
  lcd.setCursor(13, 0);
  lcd.print(numFormat(bbLimit));
  lcd.setCursor(0, 1);
  lcd.print("TOKENS/MAG");
  lcd.setCursor(13, 1);
  lcd.print(numFormat(tokenNeeded));
  switch (selectionFase){
    case 0:
      lcd.blink();
      /*will be implemented with profiles
      if (encoderUp()) {next profile}
      if (encoderDown()) {prev rpofile}*/
      if (encoderDepressState == HIGH) {selectionFase++; delay(200);}

    case 1:
      lcd.blink();
      //will be modified with profiles
      if (encoderUp()) {bbLimit++;}
      if (encoderDown()) {bbLimit--;}
      if (encoderDepressState == HIGH) {selectionFase++; delay(200);}
    
    case 2:
      lcd.blink();
      //will be modified with profiles
      if (encoderUp()) {tokenNeeded++;}
      if (encoderDown()) {tokenNeeded--;}
      if (encoderDepressState == HIGH) {selectionFase = 0; delay(200);}
  }  
}


// Displays the basic information on screen
void infoDisplay(){
  //Printing first line, depends on inizialization mode: TackNet ON or OFF
  lcd.setCursor(0, 0);
  if (radioSwitchState == HIGH){
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
  //Printing second line, will display profiles and bbLimitations
  lcd.setCursor(0, 1);
  lcd.print(profileName);
  lcd.setCursor(9, 1);
  lcd.print("  0");
  lcd.setCursor(12, 1);
  lcd.print("/" + numFormat(bbLimit));
}

//this method feeds the amount of bbs specified by the profile
void bbFeeder(){
    int bbCount = 0;
    while (bbCount < bbLimit && feedingButtonState == HIGH && emptyBoxState == HIGH){
        buttonStateUpdateReload();
        feed();
        lcd.setCursor(9,1);
        lcd.print(numFormat(bbCounter()));
    }
    feedCut();
}

//This method counts the bbs feeded and returns its value
int bbCounter(){
    if (lastbbSensorState != bbSensorState){
      if (bbSensorState == HIGH){
        bbCount++;
        lastbbSensorState = bbSensorState;
      }
      else{lastbbSensorState = bbSensorState;}
    }
    return bbCount;
}