#include "Adafruit_WS2801.h"
#include "SPI.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "WifiNetworkData.h" //ssid name and wifi password

// Data pin that led data will be written out over

// Clock pin only needed for SPI based chipsets when not using hardware SPI
char packetBuffer[2048]; //buffer to hold incoming packet,

WiFiUDP Udp;
const uint8_t dataPin  = 2;    // Yellow wire on Adafruit Pixels
const uint8_t clockPin = 0;
Adafruit_WS2801 strip = Adafruit_WS2801(320, dataPin, clockPin);

int timeSinceLastPacket;
const int timeOut = 5000;


void setup()
{
  pinMode(2, OUTPUT);
  pinMode(0, OUTPUT);
  Serial.begin(115200);
  delay(10);

  timeSinceLastPacket = 0;
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Print the IP address
  Serial.println(WiFi.localIP());
  Udp.begin(31337);
    for(int i = 0; i < strip.numPixels(); i++)
    {
      strip.setPixelColor(i, Color(0, 0, 0));
    }
    strip.show();
}

void loop()
{
  int packetSize = Udp.parsePacket();
  Udp.read(packetBuffer,2048);
  if (packetSize >= 460)
  {
    //Serial.print('[');
    for(int i = 0; i < strip.numPixels(); i++)
    {
      strip.setPixelColor(
        i,
        Color(
          (*(packetBuffer + (i*3))),
          (*(packetBuffer + ((i*3) + 1))),
          (*(packetBuffer + ((i*3) + 2)))));
      //Serial.print('(');
      //Serial.print((*(packetBuffer + (i*3))),DEC);
      //Serial.print(",");
      //Serial.print((*(packetBuffer + ((i*3) + 1))), DEC);
      //Serial.print(",");
      //Serial.print((*(packetBuffer + ((i*3) + 2))),DEC);
      //Serial.print(") ");
    }
    //Serial.println("]");
    strip.show();
    timeSinceLastPacket = millis();
  }
  if (millis() - timeSinceLastPacket > timeOut)
  {
    for(int i = 0; i < strip.numPixels(); i++)
    {

      strip.setPixelColor(i, Color(0, 0, 0));
    }
    strip.show();
  }
}

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}
