#include <SPI.h>
#include <PubSubClient.h>
#include <Ethernet.h>

/*
 * Publish Subscribe demo
 *
 * A simple platform demo for Arduino.
 * This was modified to suit cloudmqtt.com broker instead of one above.
 */

char server[] = "m12.cloudmqtt.com";

// MAC Address of Arduino Ethernet Sheild (on sticker on shield)
// This can be anything arbitrary if no Ethernet shield is there.

byte MAC_ADDRESS[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x31, 0xB8 };

EthernetClient ethClient;

// Pin 9 is the LED output pin
int ledPin = 9;
// Analog 0 is the input pin
int lightPinIn = 0;

// defines and variable for sensor/control mode
#define MODE_OFF    0  // not sensing light, LED off
#define MODE_ON     1  // not sensing light, LED on
#define MODE_SENSE  2  // sensing light, LED controlled by software
int senseMode = 0;
unsigned long time;

char message_buff[100];

// handles message arrived on subscribed topic(s)
void callback(char* topic, byte* payload, unsigned int length) {

  int i = 0;

  Serial.println("Message arrived:  topic: " + String(topic));
  Serial.println("Length: " + String(length,DEC));
  
  // create character buffer with ending null terminator (string)
  for(i=0; i<length; i++) {
    message_buff[i] = payload[i];
  }
  message_buff[i] = '\0';
  
  String msgString = String(message_buff);
  
  //Serial.println("Payload: " + msgString);
  
  if (msgString.equals("{\"command\":{\"lightmode\": \"OFF\"}}")) {
    senseMode = MODE_OFF;
  } else if (msgString.equals("{\"command\":{\"lightmode\": \"ON\"}}")) {
    senseMode = MODE_ON;
  } else if (msgString.equals("{\"command\":{\"lightmode\": \"SENSE\"}}")) {
    senseMode = MODE_SENSE;
  }
}

PubSubClient client(server, 19757, callback, ethClient);

void setup()
{
  // initialize the digital pin as an output.
  pinMode(ledPin, OUTPUT);
  
  // init serial link for debugging
  Serial.begin(9600);
  
  if (Ethernet.begin(MAC_ADDRESS) == 0)
  {
      Serial.println("Failed to configure Ethernet using DHCP");
      return;
  }
}

void loop()
{
  if (!client.connected())
  {
      // clientID, username, MD5 encoded password
      client.connect("arduino-mqtt", "oxefqvkn", "aKpQPSFiTpXp");
      client.publish("published_from_laptop", "I'm alive!");
      client.subscribe("/frommothership");
  }
  
  switch (senseMode) {
    case MODE_OFF:
      // light should be off
      digitalWrite(ledPin, LOW);
      break;
    case MODE_ON:
      // light should be on
      digitalWrite(ledPin, HIGH);
      break;
    case MODE_SENSE:
      // light is adaptive to light sensor
      
      // read from light sensor (photocell)
      int lightRead = analogRead(lightPinIn);

      // if there is light in the room, turn off LED
      // else, if it is "dark", turn it on
      // scale of light in this circit is roughly 0 - 900
      // 500 is a "magic number" for "dark"
      if (lightRead > 500) {
        digitalWrite(ledPin, LOW);
      } else {
        digitalWrite(ledPin, HIGH);
      }
      
      // publish light reading every 5 seconds
      if (millis() > (time + 5000)) {
        time = millis();
        String pubString = "{\"report\":{\"light\": \"" + String(lightRead) + "\"}}";
        pubString.toCharArray(message_buff, pubString.length()+1);
        //Serial.println(pubString);
        client.publish("io.m2m/arduino/lightsensor", message_buff);
      }
      
      
  }
  
  // MQTT client loop processing
  client.loop();
}

