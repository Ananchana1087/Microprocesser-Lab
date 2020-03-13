#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
void setup() {
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
  pinMode(A0,INPUT_PULLUP);
   pinMode(A1,INPUT_PULLUP);
}

void loop() {
  int a=digitalRead(A0);
  int b=digitalRead(A1);

   if(a==0)
  {
  display.clearDisplay();
  // text display tests
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("SW1 =      ");
  display.print("SW2 =      ");
  display.setCursor(0,0);
  display.fillCircle(42,3,3,WHITE);
  display.drawCircle(42,11,3,WHITE);
  }
  if(a==1)
  {
     display.clearDisplay();
    // text display tests
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("SW1 =      ");
  display.print("SW2 =      ");
  display.setCursor(0,0);
  display.drawCircle(42,3,3,WHITE);
   display.drawCircle(42,11,3,WHITE);
   
  }
  if(b==0)
  {
     display.clearDisplay();
  // text display tests
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("SW1 =      ");
  display.print("SW2 =      ");
  display.setCursor(0,0);
  display.fillCircle(42,11,3,WHITE);
    display.drawCircle(42,3,3,WHITE);
  }
  if(b==1)
  {
    
    // text display tests
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("SW1 =      ");
  display.print("SW2 =      ");
  display.setCursor(0,0);
  display.drawCircle(42,11,3,WHITE);
   display.drawCircle(42,3,3,WHITE);
  }
  display.setCursor(0,0);
  display.display(); // actually display all of the above
}
