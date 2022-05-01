#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#define OLED_ADDRESS   0x3C
#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);
/*
 * This is a sketch that shows speed/alitude/sat# on a oled 128x64 pixel OLED display.
 * April 23, 2022
 * This a cleaned up simple sketch. But dam it works good.
 * Updates every second.
 * ** Things I would like to add in time:
 * ** -below 10 km= 0 km for automobiles.
 * ** -
 * This sample code demonstrates the normal use of a TinyGPSPlus (TinyGPSPlus) object.
 * It requires the use of SoftwareSerial, and assumes that you have a
 *  9600-baud serial GPS device hooked up on pins 11(rx) and 12(tx).
*/
static const int RXPin = 11, TXPin = 12;
static const uint32_t GPSBaud = 9600;

// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
int speedint;
int altint;
int satint;


void setup()
{
  //Serial.begin(115200);
  ss.begin(GPSBaud);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(37, 0);
  display.print("GPS SPEED");
  display.setTextSize(1);
  display.setCursor(065, 8);
  display.print("By");
  display.setTextSize(1);
  display.setCursor(26, 16);
  display.print("Wanderingmoose");
  display.setCursor(30, 24);
  display.print("Tinkering.ca");
    display.display();
  delay(3000);
  display.clearDisplay();
  display.display();
}

void loop()
{
      shrink();
      display.clearDisplay();
      display.setTextSize(3);
      display.setCursor(40, 11);
      display.print(speedint);
      //display.print(altint);
      display.setTextSize(1);
      display.print("km/h");
      display.setTextSize(1);
      display.setCursor(10, 0);
      display.print("ALT:");
      display.print(altint);
      display.print(" m");
      display.setCursor(90, 0);
      display.print("SAT:");
      display.print(satint);
      display.display();
  smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
    //Serial.println(F("No GPS data received: check wiring"));
    display.clearDisplay();
    display.display();
    display.setCursor(040, 13);
    display.print(F("NO GPS"));
}

// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

void shrink()
{
   speedint = int (gps.speed.kmph());
   altint   = int (gps.altitude.meters());
   satint   = int(gps.satellites.value());
  }
