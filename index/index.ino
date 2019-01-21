#include <HardwareSerial.h>
#include <SoftwareSerial.h>
#include "Wifi.h"
#include "ThingSpeak.h"

#define RX 10
#define TX 11
SoftwareSerial wifiSerial(RX,TX);
HardwareSerial &computerSerial = Serial;

// Configurations live here
#include "environment.cpp"

Wifi wifi(computerSerial, wifiSerial, debugMode);
ThingSpeak thingSpeak(wifi, thingSpeakApiKey);

void setup() {
    // Initialize serial channels
    computerSerial.begin(9600);
    wifiSerial.begin(9600);

    // Mark this setup process in the serial channel with a pretty message
    computerSerial.println("");
    computerSerial.println("Setting up Arduino...");

    // Connect to hardcoded WiFi network
    if (!wifi.connectWifi(wifiSSID, wifiPassword)) {
        computerSerial.println("This sketch requires, WiFi. Please fix me!");
        return;
    }
}

int getSensorData(){
  return random(1000);
}

void loop() {
    thingSpeak.sendField(1, getSensorData());
    delay(2000);
}
