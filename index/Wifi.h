#ifndef Wifi_H
#define Wifi_H

#include <Stream.h>

class Wifi {
    Stream &debugStream;
    Stream &wifiStream;
    bool debugMode;
    bool infoMode;

    void writeDebug(String input);
    void writeInfo(String input);

    public:
    Wifi(Stream &debugStream, Stream &wifiStream, bool debugMode = true, bool infoMode = true);
    void writeWifi(String input);
    bool sendCommand(String command, String expectReply = "OK", int maxAttempts = 15);
    bool connectWifi(String ssid, String password);
    bool sendTCP(String host, int port, String payload);
};

#endif