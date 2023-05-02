#include <Arduino.h>
#include <M5Stack.h>
#include <gps.h>
#include <display.h>
#include <lora.h>
#include <neoPixel.h>
extern const unsigned char infrabel16[];
unsigned long previousMillis = 0;
unsigned long interval = 30000;
int tft_counter=0;

void fadeScreen(){
  if (millis() - previousMillis > interval)
  {
    // correct timer
    previousMillis = millis();

    // tft got to sleep after 1 minute
    tft_counter++;
    if (tft_counter==3)
    {
      if (tft_backlight == true) { tft_backlight=false; }
      // Turning off the LCD backlight
      if (tft_backlight == false)
      {
        rgb_neopixel_off();
        M5.Lcd.sleep();  M5.Lcd.setBrightness(0);
      }
      tft_counter=0;
    }
  }
}

void showScreen(){
  tft_backlight = true;
  if(tft_backlight){
    M5.Lcd.wakeup();
    M5.Lcd.setBrightness(255);
  }
}

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.Lcd.pushImage(0,0, M5.Lcd.width(), M5.Lcd.height(), (uint16_t *)infrabel16);
  delay(2000);
  initPixels();
  initLora();
  gpsinit();
  initDisplay();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(M5.BtnA.wasPressed()){
    showScreen();
    delay(200);
  }
  if(M5.BtnB.wasPressed()){
    gpsgetdata();
    delay(200);
  }
  if(M5.BtnC.wasPressed() && sending == false){
    sendPayLoad(lat,lng,alt,hdop,sat);
    tft_display_sensor_Lora(rssi);
    delay(200);
  }
  gpsgetdata();
  fadeScreen();
  delay(100);
  M5.update();
}

