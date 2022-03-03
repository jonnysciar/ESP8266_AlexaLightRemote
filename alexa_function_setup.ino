//set power state
bool onPowerState(const String &deviceId, bool &state) {
  Serial.printf("Device %s power turned %s \r\n", deviceId.c_str(), state?"on":"off");
  device_state.powerState = state;
  if (state==true){
    sender.sendNEC(0x00FFA25DUL);
  } else {
    sender.sendNEC(0x00FFE21DUL);
  }
  return true; // request handled properly
}

//set brightness
bool onBrightness(const String &deviceId, int &brightness) {
  int i;
  if(!device_state.powerState){
    sender.sendNEC(0x00FFA25DUL);
    sendStateEvent(true);
    delay(100);
  }
  
  device_state.brightness = brightness;
  for(i=0; i<4;i++){
    sender.sendNEC(0x00FF906FUL);
    delay(200);
  }
  for(i=0; i<(brightness/20);i++){ 
    sender.sendNEC(0x00FFA857UL);
    delay(200);
  }
  Serial.printf("Device %s brightness level changed to %d\r\n", deviceId.c_str(), brightness);
  return true;
}

//set color
bool onColor(const String &deviceId, byte &r, byte &g, byte &b) {
  
  device_state.color.r = r;
  device_state.color.g = g;
  device_state.color.b = b;
  //turn on light and send to sinric pro
  if(!device_state.powerState){
    sender.sendNEC(0x00FFA25DUL);
    sendStateEvent(true);
    delay(100);
  }
  setColor(device_state.color);

  Serial.printf("Device %s color changed to %d, %d, %d (RGB)\r\n", deviceId.c_str(), device_state.color.r, device_state.color.g, device_state.color.b);
  return true;
}

//set for white color
bool onColorTemperature(const String &deviceId, int &colorTemperature) {
  
  if(!device_state.powerState){
    sender.sendNEC(0x00FFA25DUL);
    sendStateEvent(true);
    delay(100);
  }
  
  sender.sendNEC(0x00FF52ADUL);
  
  Serial.printf("Device %s color temperature changed to %d\r\n", deviceId.c_str(), colorTemperature);
  return true;
}



//mapping color and set
void setColor (colore col){
  if (col.r==255 && col.g==0 && col.b==0){//rosso
    sender.sendNEC(0x00FF6897UL);
  }
  if (col.r==0 && col.g==255 && col.b==0){//verde
    sender.sendNEC(0x00FF9867UL);
  }
  if (col.r==0 && col.g==0 && col.b==255){//blu
    sender.sendNEC(0x00FFB04FUL);
  }
  if (col.r==255 && col.g==255 && col.b==0){//giallo
    sender.sendNEC(0x00FF4AB5UL);
  }
  if (col.r==255 && col.g==166 && col.b==0){//arancione
    sender.sendNEC(0x00FF30CFUL);
  }
  if (col.r==160 && col.g==33 && col.b==239){//viola
    sender.sendNEC(0x00FF10EFUL);
  }
  if (col.r==237 && col.g==130 && col.b==237){//viola
    sender.sendNEC(0x00FF10EFUL);
  }
  if (col.r==239 && col.g==255 && col.b==255){//azzurro
    sender.sendNEC(0x00FF5AA5UL);
  }
  if (col.r==173 && col.g==216 && col.b==229){//blu chiaro
    sender.sendNEC(0x00FF7A85UL);
  }
  if (col.r==255 && col.g==213 && col.b==0){//oro
    sender.sendNEC(0x00FF38C7UL);
  }
  if (col.r==159 && col.g==128 && col.b==255){//lavanda
    sender.sendNEC(0x00FF42BDUL);
  }  
  if (col.r==135 && col.g==206 && col.b==234){//celeste
    sender.sendNEC(0x00FF18E7UL);
  }  
}
