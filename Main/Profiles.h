#ifndef Profiles_h
#define Profiles_h

#include "Arduino.h"

class Profiles {
  public:
    Profiles(String profileName, int bbLimit, int tokenNeeded);
    String profileName;
    int bbLimit;
    int tokenNeeded;

    //GETTERS
    String getprofileName(){ return _profileName; }
    int getbbLimit(){ return _bbLimit; }

    int gettokenNeeded(){ return _tokenNeeded; }
    
    //SETTERS
    int setbbLimit(){ _bbLimit = bbLimit; }
    /*
    int settokenNeeded(){ _tokenNeeded = tokenNeeded; }
    */

  private:
      String _profileName;
      int _bbLimit;
      int _tokenNeeded;
}

//Constructor
Profiles::Profiles(String profileName, int bbLimit, int tokenNeeded){
  int _profileName = profileName;
  int _bbLimit = bbLimit;
  int _tokenNeeded = tokenNeeded;
}
