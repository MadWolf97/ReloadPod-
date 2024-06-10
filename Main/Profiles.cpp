#include "Arduino.h"
#include "Profiles_h"


//This method lets you change the bbLimit for the active Profile
void Profiles::changebbLimit(){

}

//this method feeds the amount of bbs specified by the profile
void Profiles::bbFeeder(int bbLimit){
    int bbCount = 0;
    while (bbCount < this.bbLimit){
        buttonStateUpdateReload();
        feed();
        lcd.setCursor(9,1);
        lcd.print(numFormat(bbCounter()));
    }
}

//This method counts the bbs feeded and returns its value
int Profiles::bbCounter(int bbSensorState, int lastbbSensorState, int bbCount){
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