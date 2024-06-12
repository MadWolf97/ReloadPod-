#include "Profiles_h"


Profiles(String profileName, int bbLimit, int tokenNeeded){
  String profileName;
  int bbLimit;
  int tokenNeeded;
}

//CONSTRUCTOR
Profiles::Profiles(String profileName, int bbLimit, int tokenNeeded){
  int _profileName = profileName;
  int _bbLimit = bbLimit;
  int _tokenNeeded = tokenNeeded;
}
 
//GETTERS
String getprofileName(){ 
  return _profileName; 
}
int getbbLimit(){ 
  return _bbLimit; 
}

int gettokenNeeded(){ 
  return _tokenNeeded; 
}

//SETTERS
int setbbLimit(int bbLimit){ 
  _bbLimit = bbLimit; 
}
/*
int settokenNeeded(int tokenNeeded){ 
  _tokenNeeded = tokenNeeded; 
}
*/