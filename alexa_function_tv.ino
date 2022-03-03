struct {
  bool state = false;
  int channelState = 0;
} tv_state;

//set power state
bool onPowerState_tv(const String &deviceId, bool &state) {
  tv_state.state = state;
  sender.sendNEC(0x0020DF10EF);
  Serial.printf("Device %s power turned %s \r\n", deviceId.c_str(), state?"on":"off");
  return true; // request handled properly
}

//set mute/unmute
bool onMute(const String &deviceId, bool &mute) {
  sender.sendNEC(0x0020DF906F);
  Serial.printf("Device %s is %s\r\n", deviceId.c_str(), mute?"muted":"unmuted");
  return true; // request handled properly
}

//adjust volume
bool onAdjustVolume(const String &deviceId, int &volumeDelta, bool volumeDefault) {
  int i;
  if (volumeDelta>0){
    if (volumeDelta==10) volumeDelta=2;
    for(i=0; i<volumeDelta; i++){
      sender.sendNEC(0x0020DF40BF);
      delay(100);
    }
  }
  if (volumeDelta<0){
    if (volumeDelta==-10) volumeDelta=-2;
    for(i=0; i>volumeDelta; i--){
      sender.sendNEC(0x0020DFC03F);
      delay(100);
    }
  }
  Serial.printf("Device %s volume changed by %d\r\n", deviceId.c_str(), volumeDelta);
  return true;
}

bool onSelectInput(const String &deviceId, String &input) {
  sender.sendNEC(0x0020DFD02F);
  delay(100);
  sender.sendNEC(0x0020DFD02F);
  delay(100);
  sender.sendNEC(0x0020DF22DD);
  Serial.printf("Device %s input changed to %s\r\n", deviceId.c_str(), input.c_str());
  return true;
}

//change channel
bool onChangeChannelNumber(const String& deviceId, int channelNumber, String& channelName) {
  
  channelName = String(channelNumber);
  send_numbers(channelNumber);
  tv_state.channelState = channelNumber;
  
  Serial.printf("Change to channel to %d (channel name \"%s\")\r\n", channelNumber, channelName.c_str());
  return true;
}

//send whole number digit by digit
void send_numbers (int num){
  //Serial.println(num);
  if (num>0){
    send_numbers(num/10);
    send_number(num%10);
    delay(200);
  }
}

//send digit
void send_number (int n) {
  switch(n){
    case 1:
      sender.sendNEC(0x0020DF8877);
      break;
    case 2:
      sender.sendNEC(0x0020DF48B7);
      break;
    case 3:
      sender.sendNEC(0x0020DFC837);
      break;
    case 4:
      sender.sendNEC(0x0020DF28D7);
      break;
    case 5:
      sender.sendNEC(0x0020DFA857);
      break;
    case 6:
      sender.sendNEC(0x0020DF6897);
      break;
    case 7:
      sender.sendNEC(0x0020DFE817);
      break;
    case 8:
      sender.sendNEC(0x0020DF18E7);
      break;
    case 9:
      sender.sendNEC(0x0020DF9867);
      break;
    case 0:
      sender.sendNEC(0x0020DF08F7);
      break;
  }
}
