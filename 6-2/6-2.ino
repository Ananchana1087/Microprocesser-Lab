#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DS1302.h>
DS1302 rtc(2, 3, 4);
Time t;
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
void setup() {
  // Set the clock to run-mode, and disable the write protection
rtc.halt(false);
rtc.writeProtect(false);
 
// Setup Serial connection
Serial.begin(9600);
 
// The following lines can be commented out to use the values already stored in the DS1302
// rtc.setDOW(MONDAY); // Set Day-of-Week to FRIDAY
// rtc.setTime(15, 1, 0); // Set the time to 12:00:00 (24hr format)
// rtc.setDate(3, 6, 2019); // Set the date to August 6th, 2010
  Serial.begin(9600);

  Serial.println("OLED FeatherWing test");
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

  Serial.println("OLED begun");

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  // Clear the buffer.
  display.clearDisplay();
  display.display(); 
}

void loop() {
  // Get data from the DS1302
t = rtc.getTime();
  display.clearDisplay();
  // text display tests
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print("year  : ");
  display.println(t.year);
   display.print("month : ");
  display.println(rtc.getMonthStr());
   display.print("day   : ");
  display.println(t.date);
   display.print("itme  : ");
  display.print(t.hour);
  display.print(":");
  display.print(t.min);
   display.print(":");
  display.println(t.sec);
  display.setCursor(0,0);
  display.display(); // actually display all of the above
}
//
//void loop()
//{
//// Get data from the DS1302
//t = rtc.getTime();
// 
//// Send date over serial connection
//Serial.print("Today is the ");
//Serial.print(t.date, DEC);
//Serial.print(" Day,");
//Serial.print(rtc.getMonthStr());
//Serial.print(" Month,");
//Serial.print(t.year, DEC);
//Serial.println(" year");
// 
//// Send Day-of-Week and time
//Serial.print(t.hour, DEC);
//Serial.print(" hour,");
//Serial.print(t.min, DEC);
//Serial.print(" minute,");
//Serial.print(t.sec, DEC);
//Serial.println(" second");
// 
//// Send a divider for readability
//Serial.println(" - - - - - - - - - - - - - - - - - - - - -");
// 
//// Wait one second before repeating :)
//delay (1000);
//}
