#ifdef ENABLE_DEBUG
       #define DEBUG_ESP_PORT Serial
       #define NODEBUG_WEBSOCKETS
       #define NDEBUG
#endif 

#include <Arduino.h>
#include <IRsend.h>
#include <IRremoteESP8266.h>

#include <WiFiManager.h> 


#include "SinricPro.h"
#include "SinricProLight.h"

#define APP_KEY           "db74d5ee-87d0-4a5d-9306-e68d43a64cf2"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "1940dcd0-27da-4197-9612-a46cb0bfa6a9-728edbf1-3980-4abb-8a9d-84153d18847f"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define LIGHT_ID          "5e43e7647a70145df38063d4"    // Should look like "5dc1564130xxxxxxxxxxxxxx"
#define BAUD_RATE         115200                // Change baudrate to your need

//ir sender setup
#define IR 4
#define led 14
IRsend sender(IR);

//define struct to track light state
typedef struct {
    byte r = 0;
    byte g = 0;
    byte b = 0;
} colore;

struct {
  bool powerState = false;
  int brightness = 0;
  colore color ;
} device_state; 

// main setup function
void setup() {
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
  sender.begin();
  Serial.begin(BAUD_RATE);
  Serial.printf("\r\n\r\n");
  setupWiFi();
  setupSinricPro();
}

void loop() {
  SinricPro.handle();
}
