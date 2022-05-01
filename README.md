# GPS-Nano-and-Laser-Cut-case
GPS module and Nano with 0.96" OLED Display in a laser cut enclosure
Items used:
Arduino Nano
TELCO132 GPS module
0.96" OLED Display (128x64) I2C interface
Laser Cut Enclosure

Found the cheap GPS module at aliexpress( approx $6 CDN) so decided to give it a try with a NANO module.
Found the TINYGPS++ library that works great for parsing the NEMA data stream.
Used the Adafruit SSD1306 library for the OLED display.

I was looking for a way to check my speedometer in my vechicles. With this unit I can confirm my speedometer with both Google maps and a GPS. More time then not, the car's speedometer was out almost 10 % for my vechicles. In Canada if your speedometer is out >= 10 % of actual, the dealer has to make changes to correct. If < 10% actual, it is your problem.

Other information I learned from GPS and accuracy. If linked to less then 7 satillites it is not very accuracte altitude and speed can be out over 20%. More than 7 satillites and it with in .5% for both speed and altitude.

On startup the TELCO132 module can take 5 minutes to link to any satillites(Cool Start). Reading the data sheet for the TECLO132 will tell you more.
The TELCO132 is a RS-232 serial unit, and is defaulted to 9600 8N1.




Arduino Code:
/*********************************************************
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
