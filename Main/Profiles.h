#ifndef Profiles_h
#define Profiles_h

#include <Arduino.h>

class Profiles {
  public:
    Profiles(String profileName, int bbLimit, int tokenNeeded);
    String profileName;
    int bbLimit;
    int tokenNeeded;

    //GETTERS
    String getprofileName();
    int getbbLimit();

    int gettokenNeeded();
    
    //SETTERS
    int setbbLimit(){;
    /*
    int settokenNeeded();
    */

  private:
      String _profileName;
      int _bbLimit;
      int _tokenNeeded;
}

#endif