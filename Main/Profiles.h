#ifndef Profiles_h
#define Profiles_h

#include "Arduino.h"

class Profiles {
  public:
    Profiles(String profileName, int bbLimit, int tokenNeeded);
    void bbFeeder(int bblimit);
    int bbCounter();
    int bbCount;
    int bbLimit;

  private:
      int _tokenNeeded;


}

//Constructor
Profiles::Profiles(String profileName, int bbLimit, int tokenNeeded){
  int profileName = profileName;
  int bbLimit = bbLimit;
  int _tokenNeeded = tokenNeeded;
}

void Profiles