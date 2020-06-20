#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

byte mac[] {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 0, 190);
EthernetServer server(80);

const int rainPin=A0;
const int treshold=500;

void setup() {
  
}

void loop() {
  
}