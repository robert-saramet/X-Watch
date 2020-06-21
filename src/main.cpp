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

byte humIcon[]={
  B00100,
  B00100,
  B01010,
  B01010,
  B10001,
  B10001,
  B01110
};


/* const uint64_t zero[]={
  0x0007050505050700
};

const uint64_t one[]={
  0x0007020202030200
}; */



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

  Serial.print("Server IP: ");
  Serial.println(Ethernet.localIP());

  lcd.init();
  lcd.backlight();
  lcd.createChar(11, tempIcon);
  lcd.createChar(12, humIcon);
}

void loop() {
  int temp = dht.readTemperature();
  int hum = dht.readHumidity();
  int rainValue = analogRead(rainPin);

  EthernetClient client=server.available();
  if (client){
    Serial.println("New Client");
    bool currentLineIsBlank = true;
    while (client.connected()){
      if (client.available()){
        char c = client.read();
        Serial.write(c);
        if (c == '\n' && currentLineIsBlank){
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("Refresh: 5");
          client.println();

          client.println("<!DOCTYPE HTML>");
          client.println("<html");
          client.println("<h2>");

          client.print("Temperatura: ");
          client.print(temp);
          client.println("C");
          client.println("</br>");

          client.print("Umiditate: ");
          client.print(hum);
          client.println("%");
          client.println("</br>");

          if(rainValue < treshold)
            client.println("Ploua");
          else client.println("Nu ploua");

          client.println("</h2>");
          client.println("</html>");
          client.println("</br>");
          break;
        }
        if (c == '\n')
          currentLineIsBlank = true;
        else if (c != '\r')
          currentLineIsBlank = false;
      }
    }
    delay(1);
    client.stop();
    Serial.println("Client Disconnected");
  }
  lcd.clear();
  lcd.write((byte)0);
  lcd.print("Temperatura: ");
  lcd.print(temp);
  lcd.println("C");

  lcd.setCursor(0,1);
  lcd.write((byte)1);
  lcd.print("Umiditate: ");
  lcd.print(hum);
  lcd.println("%");

  lcd.setCursor(0,2);
  if(rainValue < treshold)
    lcd.println("Ploua");
  else lcd.println("Nu ploua");
}