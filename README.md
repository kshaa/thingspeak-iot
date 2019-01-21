# Arduino + ESP8266 + ThingSpeak
First steps in IoT.  
The base idea and most of the code is sourced from this Medium post - https://medium.com/@cgrant/using-the-esp8266-wifi-module-with-arduino-uno-publishing-to-thingspeak-99fc77122e82  
My version uses classes, because I thought that would be neat  

# What is this?
This code/sketch implements:
- Arduino microcontroller speaking to an ESP8266 (wi-fi) microcontroller
- Sending TCP packets to [ThingSpeak](https://thingspeak.com)
- The payload sent to ThingSpeak fills a "field" in a "channel" with random integers from 0 to 1000

# Wiring
| ESP8266 | Arduino |
|---------|---------|
| RX      | 11      |
| TX      | 10      |
| GND     | GND     |
| VCC     | 3.3V    |
| CH_PD   | 3.3V    |

# Configuration
`environment.sample.cpp` contains hardcoded configurations/secrets.  
Populate the file and move it to `environment.cpp`.