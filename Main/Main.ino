#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

//PIN ASIGMENTS WILL BE CHANGED LATER
//Buttons pins asignations
const int emptyBoxPin = 8;
const int feedingButtonPin =14;
const int bbSensorPin = 15;
const int loadingModePin = 16;
const int displayModePin = 17;
const int encoderDepressPin = 18;
// encoder and radio mode switches will be added later

//Actuators pin asigments
const int motor = 19;

//Variables reading set up
int feedingButtonState = 0;
int emptyBoxState = 0;
int bbSensorState = 0;
int loadingModeState = 0;
int displayModeState = 0;
int encoderDepressState = 0;

//Utility variables
int lastbbSensorState = 0;

void setup() {
  // INITIAL PARAMETERS

  // Button input/output set
  pinMode(feedingButtonPin, INPUT);
  pinMode(emptyBoxPin, INPUT);
  pinMode(bbSensorPin, INPUT);
  pinMode(loadingModePin, INPUT);
  pinMode(displayModePin, INPUT);
  pinMode(motor, OUTPUT);

  // LCD sizing
  lcd.begin(16, 2);

  //TacNet comunications will be added here

  //Activation message
  lcd.setCursor(0, 0);
  lcd.print("Ativado");
  delay(1000); 
}

void loop() {
  //Button variable initialization
  feedingButtonState = digitalRead(feedingButtonPin);
  emptyBoxState = digitalRead(emptyBoxPin);
  bbSensorState = digitalRead(bbSensorPin);
  loadingModeState = digitalRead(loadingModePin);
  displayModeState = digitalRead(displayModePin);
  encoderDepressState = digitalRead(encoderDepressPin);

  //Independent variable Initialization
  int bbCount = 0;
  
  
  //MAIN PROGRAM
  if (emptyBoxState == HIGH){
    info();
    if (feedingButtonState == HIGH){
      feed();
    }
  }

  //Empty deposit ALERT
  if (emptyBoxState == LOW){
    lcd.setCursor(0, 0);
    lcd.print("Deposito Vacio  ");
    lcd.setCursor(0, 1);
    lcd.print("Dial + tubo     ");
    if (feedingButtonState == HIGH){
      /* this is for profile limitations
      if (bbCount => bbLimit){
        break;
      }
      */
      feed();
    }
    else{
      feedCut();
    }
  }
}

void info(){
  lcd.setCursor(0, 0);
  lcd.print("No loading limit  ");
  lcd.setCursor(0, 1);
  lcd.print("Fusil"); //Later will be changed by profile selections
  lcd.setCursor(10, 1);
  lcd.print("30"); //Later will be changed by profile selections
  lcd.setCursor(13,1);
  lcd.print(bbCounter());
}

//This method counts the amount of bbs that have been feed
int bbCounter(){
  int bbCount = 0;
  bbSensorState = digitalRead(bbSensorPin);
  //Only counts the times the sensor has gone from of to on
  if (lastbbSensorState != bbSensorState){
    if (bbSensorState == HIGH){
      bbCount++;
      lastbbSensorState = bbSensorState;
    }
    else{
      lastbbSensorState = bbSensorState;
    }
  }
  return bbCount;
}

//This will feed bbs to your magazine
void feed() {
  digitalWrite(motor, HIGH); //girar motor
  //bbCounter();
}

void feedCut(){
  digitalWrite(motor, LOW);
}


