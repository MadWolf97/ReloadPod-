//TACKNET REALTED FUNCTIONS
//This method will decide what to do after each reload
void tokenManager(){
  if (radioSwitchState == HIGH){
    //Will be changed with TackNet
    token = token - tokenNeeded;      
    /*Will be implemented with TackNet
    this part will need to send the tokens consumed during the last reoad to the main unit
    tokenConsumption(token - tokenNeeded);
    */
  }
  else{
    /* This is only used for getting the statitics 
    needed for equilibrating future games */
    token = token + tokenNeeded;
  }
}

//this method shows how many mags you can reload
int magCounter(){
  int mags = token / tokenNeeded;
  if (mags > 0){
      aviability = true;
    }
    else{
      aviability = false;
    }
  return mags;
}

/*Will be implemented with TackNet
//This method gets the information from the main unit
int tokenUpdate(){ 
  network.update();
  network.read(avaliableTokens); // Read the incoming data
  return avaliableTokens;
}

//This method comunicates the tokens consumed by the last refill to the main unit
void tokenConsumption (int token){
  network.update();
  unsigned long now = millis();
  if (now - last_sent >= interval) {   // If it's time to send a data, send it!
    last_sent = now;
    RF24NetworkHeader header(master00);   // (Address where the data is going)
    network.write(token); // Send the data
  }
}
*/