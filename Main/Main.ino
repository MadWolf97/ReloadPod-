#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

//PIN ASIGMENTS WILL BE CHANGED LATER
// Buttons pins asignations
const int feedingButtonPin = 8;
const int emptyButtonPin = 9;
const int bbSensorPin = 10;
const int loadingModePin = 11;
const int displayModePin = 12;
// encoder adn radio mode switches will be added later

//Actuators pin asigments
const int motor = 13;

//Variables reading set up
int feedingButton = 0;
int emptyButton = 0;
int bbSensor = 0;
int loadingMode = 0;
int displayMode = 0;

//Utility variables
int lBS = 0;

void setup() {
  // INITIAL PARAMETERS

  // Button input/output set
  pinMode(feedingButtonPin, INPUT);
  pinMode(emptyButtonPin, INPUT);
  pinMode(bbSensorPin, INPUT);
  pinMode(loadingModePinv, INPUT);
  pinMode(displayModePin, INPUT);
  pinMode(motor, OUTPUT);

  // LCD sizing
  lcd.begin(16, 2);

  //TacNet comunications will be added here

}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Ativado");

  //Variable Initialization
  int bbCount = 0;
  
  //Main program
  while 
}

void main(){
  lcd.setCursor(0, 0);
  lcd.print("Fusil"); //Later will be changed by profile selections
  lcd.setCursor(0,1);
  lcd.print(bbCounter());
}

//This method counts the amount of bbs that have been feed
int bbCounter(){
  cBS = digitalRead(bbSensorPin);
  //Only counts the times the sensor has gone from of to on
  if (lBS != cBS){
    if (cBS == HIGH){
      bbCount++;
      lBS = cBS;
    }
    else{
      lBS = cBS;
    }
  }
  return bbCount;
}

//This will feed bbs to your magazine
void feed() {
  digitalWrite(motor, HIGH); //girar motor
  bbCounter();
}


