/* 
    --------------------------------------------------------------
    |Library|      Weather     |LED Matrix|   Display   |Ethernet|
    |-------|------------------|----------|-------------|--------|
    |  Name |DHT Sensor Library|LedControl|LiquidCrystal|Ethernet|
    |-------|------------------|----------|-------------|--------|
    |Creator|     Adafruit     |  wayoda  |John Rickman |Arduino |
    --------------------------------------------------------------


    ---------------------------------
    |   DHT11 VCC   |   Shield 5V   |
    |   DHT11 GND   |   Shield GND  |
    |   DHT11 OUT   |   Shield D2   |
    ---------------------------------
    |   Rain VCC    |   Mega D22    |
    |   Rain GND    |   Shield GND  |
    |   Rain OUT    |   Shield A0   |
    ---------------------------------
    |   LCD VCC     |   Mega D24    |
    |   LCD GND     |   Shield GND  |
    |   LCD SDA     |   Mega SDA    |
    |   LCD SCL     |   Mega SCL    |
    ---------------------------------
*/

#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

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