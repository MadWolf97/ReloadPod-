#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

//PIN ASIGMENTS WILL BE CHANGED LATER
//Buttons pins asignations
const int feedingButtonPin = 8;
const int emptyBoxPin = 9;
const int bbSensorPin = 10;
const int loadingModePin = 11;
const int displayModePin = 12;
const int encoderDepressPin = 13;
// encoder and radio mode switches will be added later

//Actuators pin asigments
const int motor = 16;

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

}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Ativado");

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
  
  
  while (emptyBoxState == HIGH){
    info();
    while (feedingButtonState == HIGH){
      feed();
    }
  }
  //Empty deposit ALERT
  else{
    lcd.setCursor(0, 0);
    lcd.print("Deposito Vacio");
    lcd.setCursor(0, 1);
    lcd.print("Dial + tubo");
    if ((feedingButtonState == HIGH) && (encoderDepressState == HIGH)){
      feed();
    }
  }
}

void info(){
  lcd.setCursor(0, 0);
  lcd.print("No loading limit");
  lcd.setCursor(0, 1);
  lcd.print("Fusil"); //Later will be changed by profile selections
  lcd.setCursor(0, 13);
  lcd.print("30"); //Later will be changed by profile selections
  lcd.setCursor(13,1);
  lcd.print(bbCounter());
}

//This method counts the amount of bbs that have been feed
int bbCounter(){
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
  bbCounter();
}


