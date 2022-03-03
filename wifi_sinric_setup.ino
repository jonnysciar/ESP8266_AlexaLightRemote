void setupWiFi(){
  Serial.println("Start Manager.");
  
  /*WiFiManager wifiManager;
  //wifiManager.resetSettings();
  wifiManager.setAPStaticIPConfig(IPAddress(192,168,1,1), IPAddress(192,168,1,1), IPAddress(255,255,255,0));
  wifiManager.autoConnect();*/

  WiFiManager wifiManager;
  //wifiManager.resetSettings();
  wifiManager.setTimeout(300);
  wifiManager.setAPStaticIPConfig(IPAddress(192,168,1,1),IPAddress(192,168,1,1), IPAddress(255,255,255,0));
  
  //If no configured after 5 mins restart
  if(!wifiManager.autoConnect("faretti")){
    Serial.print("RESET...");
    ESP.reset();
  }

  Serial.println("Connected.");
}

//send event on changing power state
void sendStateEvent(bool state){
  
  SinricProLight &light = SinricPro[LIGHT_ID];
  
  device_state.powerState = state; 
  light.sendPowerStateEvent(state); 
  //light.sendColorEvent(device_state.color.r, device_state.color.g, device_state.color.b);
  Serial.printf("Device %s power turned %s \r\n", LIGHT_ID, state?"on":"off");
}

void setupSinricPro() {
  // get a new Light device from SinricPro
  SinricProLight &myLight = SinricPro[LIGHT_ID];

  // set callback function to light
  myLight.onPowerState(onPowerState);
  myLight.onBrightness(onBrightness);
  myLight.onColorTemperature(onColorTemperature);
  myLight.onColor(onColor);

  // get a new Light device from SinricPro
  SinricProTV &myTV = SinricPro[TV_ID];

  // set callback functions to tv
  myTV.onPowerState(onPowerState_tv);
  myTV.onChangeChannelNumber(onChangeChannelNumber);
  myTV.onAdjustVolume(onAdjustVolume);
  myTV.onMute(onMute);
  myTV.onSelectInput(onSelectInput);
  
  // setup SinricPro
  SinricPro.onConnected([](){ Serial.printf("Connected to SinricPro\r\n"); }); 
  SinricPro.onDisconnected([](){ Serial.printf("Disconnected from SinricPro\r\n"); });
  SinricPro.begin(APP_KEY, APP_SECRET);
}
