#ifndef ThingSpeak_H
#define ThingSpeak_H

#include "Wifi.h"

class ThingSpeak {
    Wifi &wifi;
    static const String hostname;
    static const int port;
    String apiKey;

    public:
    ThingSpeak(Wifi &wifi);
    ThingSpeak(Wifi &wifi, String apikey);
    bool sendField(int fieldNumber, String value);
    bool sendField(int fieldNumber, int value);
    void setApiKey(String apiKey);
};

#endif