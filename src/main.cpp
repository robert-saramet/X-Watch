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

byte tempIcon[]={
    B00100,
    B01010,
    B01010,
    B01110,
    B01110,
    B11111,
    B11111,
    B01110
};

byte humIcon[]=
{
  B00100,
  B00100,
  B01010,
  B01010,
  B10001,
  B10001,
  B01110
};

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4);

byte mac[] {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 0, 190);
EthernetServer server(80);

const int rainPin=A0;
const int treshold=500;

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  server.begin();
  dht.begin();
  Serial.println("Server IP: " + Ethernet.localIP());

  lcd.init();
  lcd.backlight();
  lcd.createChar(0, tempIcon);
  lcd.createChar(1, humIcon);

}

void loop() {
  
}