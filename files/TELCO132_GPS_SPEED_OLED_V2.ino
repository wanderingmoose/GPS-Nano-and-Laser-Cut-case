/*
 * This sketch is for working with the TELCO132_GPS module and a 128x64 OLED module.
 * Works April 21, 2022
 *
 * 
 */
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#define OLED_ADDRESS   0x3C
#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);
int RX = 12, TX = 11;
TinyGPSPlus gps;
SoftwareSerial gpssoft(RX, TX);
void setup()
{
  Serial.begin(9600);
  gpssoft.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  display.clearDisplay();
   display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 2);
  display.print("GPS SPEED");
  display.setTextSize(1);
  display.setCursor(00, 13);
  display.print("For");
  display.setTextSize(1);
  display.setCursor(00, 22);
  display.print("You");
  display.display();
  delay(3000);
  display.clearDisplay();
  display.display();
}
void loop()
{

//  display.display();
  while (gpssoft.available() > 0)
    if (gps.encode(gpssoft.read()))
    displaysat();
    displayspeed();
  }
void displayspeed()
{
  if (gps.speed.isValid())
  {
    display.clearDisplay();
    display.setTextSize(3);
    //display.setCursor(10, 11);
     display.setCursor(10, 8);
    display.print(gps.speed.kmph());
    display.display();
  }
  else
  {
    display.setTextSize(1);
    display.setCursor(1, 0);
    display.print("No Data!!!");
    display.display();
  }
  delay(100);
}

void displaysat()
{
 if (gps.satellites.isValid())
 {
    //display.clearDisplay();
    display.setTextSize(1);
   //display.setCursor(40, 11);
        display.setCursor(110, 0);
    display.print(gps.satellites.value());
    
    display.display();
  }
  else
  {
    display.setTextSize(1);
   display.setCursor(70, 0);
   display.print("No # Data");
   display.display();
 }
 delay(100);
}
