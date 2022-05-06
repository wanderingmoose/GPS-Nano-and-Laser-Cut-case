#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#define OLED_ADDRESS   0x3C
#define OLED_RESET -1
#define Vin A3      
Adafruit_SSD1306 display(OLED_RESET);
/*
 * This is a sketch that shows speed/alitude/sat# on a oled 128x64 pixel OLED display.
 * April 23, 2022
 * May 5, 2022---added voltage to the display. A3 with voltage divider
 * This a cleaned up simple sketch. But dam it works good.
 * Updates every second.
 
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
// Voltage setup
float vlts;
int raw;
int raw1;
int vlts1;
const float Vref = 5.00;                // Actual voltage and resistor values can be set here. 
const float R1 =  100950.0;             // R1 is nominally 100000.0
const float R2 =   22000.0;             // R2 is nominally 22000.0
const float resDiv = (R2/(R1 + R2));    // Resistor divider factor applied to measured voltage.

void setup()
{
  Serial.begin(115200);
   pinMode(Vin, INPUT);    
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
      //vcs();
      display.clearDisplay();
      display.setTextSize(4);
      display.setCursor(0, 0);
      display.print(speedint);
      //display.print(altint);
      display.setTextSize(0);
      display.setCursor(77, 0);
      display.print("km/h");
      display.setTextSize(1);
      display.setCursor(77, 9);
      display.print("ALT:");
      display.print(altint);
      display.setCursor(77, 17);
      display.print("SAT:");
      display.print(satint);
      vcs();
      display.setTextSize(1);
      display.setCursor(77,25);
      display.print("Vdc:");
     // display.print(analogRead(Vin));
      display.print(vlts);
      display.display();
      /*
      Serial.print("Volts:  ");
      Serial.println(vlts);
      Serial.println(vlts1);
      Serial.println(raw);
      Serial.println(raw1);
      Serial.println(analogRead(Vin));
      Serial.print("ALT:  ");
      Serial.println(altint);
      Serial.print("SATS:  ");
      Serial.println(satint);
      Serial.print("Speed:  ");
      Serial.println(speedint);
      Serial.println("______________");
      Serial.println("______________");
      */
      
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

  void vcs()
  {
     int raw = 0;                                // Get voltage at R1-R2 junction.
 for (byte i=0;i<10;i++) {
    raw += analogRead(Vin);
    delay(10);
 }
 raw1 = (raw / 10);
 float vlts1 = ((raw1 / 1024.0) * Vref);
 vlts = (vlts1 / resDiv);
 }
