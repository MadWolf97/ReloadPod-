#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

//PIN ASIGMENTS MIGHT BE CHANGED LATER
  //Buttons pins asignations
  const int emptyBoxPin = 8;
  const int feedingButtonPin =14;
  const int bbSensorPin = 15;
  const int loadingModePin = 16;
  /* will be added with profiles implementation
  const int encoderUpPin
  const int encoderDownPin
  */
  const int encoderDepressPin = 18;
  const int radioSwitchPin = 19;

  //Actuators pin asigments
  const int motor = 19;

//VARIABLES INITIALLIZATION
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
  radioSwitchState = 0;

  //Utility variables
  int lastbbSensorState = 0;

void setup() {
  // INITIAL PARAMETERS

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



  //Preset Profiles
  /*
  ("Pistola",14);
  ("Franco",10);
  ("Selecto",20);
  ("Asalto",30);
  ("Apollo",180);


  ("LowCap",90);
  ("MidCap",120);
  ("MidCap",160);
  */

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

}

void loop() {
  //Button variable initialization  
  emptyBoxState = digitalRead(emptyBoxPin);
  feedingButtonState = digitalRead(feedingButtonPin);
  bbSensorState = digitalRead(bbSensorPin);
  /* will be added with profiles implementation
  encoderUpState = digitalRead(encoderUpPin);      
  encoderDownState = digitalRead(encoderDownPin);   
  */
  encoderDepressState = digitalRead(encoderDepressPin);

  //Independent variable Initialization

  

  //MAIN PROGRAM
  if(emptyBoxState == LOW){
    emptyAlert();
  }

  while (emptyBoxState == HIGH && feedingButtonState == LOW){
    info();
  }

  while (emptyBoxState == HIGH && feedingButtonState == HIGH){
    bbCounter();
    feedCut();
    //Delay in order to see the bbCount
    delay(3000); 
  }
}

// Displays the basic information on screen
void info(){
  lcd.setCursor(0, 0);
  lcd.print("Mags left  ");
  lcd.setCursor(13, 0);
  lcd.print("INF"); // Will be imnplemented later with TackNet
  lcd.setCursor(0, 1);
  lcd.print("Asalto "); // Later will be changed by profile selections
  lcd.setCursor(12, 1);
  lcd.print("/ 30"); // Later will be changed by profile selections
}

// Empty deposit ALERT and REFILLING
void emptyAlert{
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
void bbCounter (){
  //Only counts the times the sensor has gone from of to on
  int bbCount = 0;
  int bbLimit = 30; //will be changed later with profile implementation
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
    lcd.print (bbCount);
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
