#include "Wifi.h"
#include <Stream.h>

void Wifi::writeDebug(String input) {
    if (debugMode) debugStream.println("[DEBUG]: " + input);
}

void Wifi::writeInfo(String input) {
    if (infoMode) debugStream.println("[INFO]: " + input);
}

Wifi::Wifi(Stream &t_debugStream, Stream &t_wifiStream, bool t_debugMode = true, bool t_infoMode = true)
    : debugStream(t_debugStream), wifiStream(t_wifiStream)
{
    debugMode = t_debugMode;
    infoMode = t_infoMode;
}

void Wifi::writeWifi(String input) {
    writeDebug("WiFi command: '" + input + "'");
    wifiStream.println(input);
}

bool Wifi::sendCommand(
    String command,
    String expectReply = "OK",
    int maxAttempts = 15
) {
    writeDebug("WiFi command: '" + command + "'");
    for (int attempt = 0; attempt < maxAttempts; attempt++) {
        writeWifi(command);

        char commandPointer = * expectReply.c_str();
        if (wifiStream.find(commandPointer)) {
            writeDebug("Wi-Fi command '" + command + "' success");

            return true;
        }
    }
    
    writeDebug("Wi-Fi command '" + command + "' failure");
    return false;
}

bool Wifi::connectWifi(String ssid, String password) {
    bool wifiSuccess = true;
    wifiSuccess = wifiSuccess && sendCommand("AT+RST");
    wifiSuccess = wifiSuccess && sendCommand("AT+CWMODE=1");
    wifiSuccess = wifiSuccess && sendCommand("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"");

    if (wifiSuccess) {
        writeInfo("Wifi connection established!");
    } else {
        writeInfo("Wifi connection couldn't be established!");
    }

    return wifiSuccess;
}

bool Wifi::sendTCP(String host, int port, String payload) {
    int magicalPayloadByteBuffer = 4;

    // Enable multiple TCP connections
    sendCommand("AT+CIPMUX=1");

    // Start TCP connection
    sendCommand("AT+CIPSTART=0,\"TCP\",\"" + host + "\"," + port);

    // Attach TCP window size
    sendCommand("AT+CIPSEND=0," + String(payload.length() + magicalPayloadByteBuffer));

    // Attach segment / payload
    writeWifi(payload);

    // Close connection
    bool sendTCPSuccess = sendCommand("AT+CIPCLOSE=0");

    if (sendTCPSuccess) {
        writeInfo("Wifi successfully sent TCP packet '" + payload + "'");
    } else {
        writeInfo("Wifi failed to send TCP packet '" + payload + "'");
    }

    return sendTCPSuccess;
}