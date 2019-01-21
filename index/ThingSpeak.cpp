#include "ThingSpeak.h"
#include "Wifi.h"

const String ThingSpeak::hostname = "api.thingspeak.com";
const int ThingSpeak::port = 80;

ThingSpeak::ThingSpeak(Wifi &t_wifi)
    : wifi(t_wifi)
{
}

ThingSpeak::ThingSpeak(Wifi &t_wifi, String t_apiKey)
    : wifi(t_wifi)
{
    apiKey = t_apiKey;
}

bool ThingSpeak::sendField(int fieldNumber, String value) {
    String payload = "GET /update?api_key=" + apiKey + "&field" + fieldNumber + "=" + String(value);

    wifi.sendTCP(hostname, port, payload);
}

bool ThingSpeak::sendField(int fieldNumber, int value) {
    String payload = "GET /update?api_key=" + apiKey + "&" + fieldNumber + "=" + String(value);

    wifi.sendTCP(hostname, port, payload);
}

void ThingSpeak::setApiKey(String t_apiKey) {
    apiKey = t_apiKey;
}