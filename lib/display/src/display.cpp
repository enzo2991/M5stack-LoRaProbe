#include <Arduino.h>
#include <M5Stack.h>
#include <TinyGPS++.h>
#include <Free_Fonts.h>
#include <gps.h>
#include <neoPixel.h>
uint8_t bat = M5.Power.getBatteryLevel();
const char* room_screen  = "Infrabel";

/*-------------------------------------------------------------------------------*/
/* Function void tft_display_room_screen(String room_name, long int room_bg)     */
/*                                                                               */
/* TASK    : show tft display room screen                                        */
/* UPDATE  : 22.09.2020                                                          */
/*-------------------------------------------------------------------------------*/
void tft_display_room_screen(String room_name, long int room_bg) 
{
  M5.Lcd.fillScreen(TFT_WHITE);
  M5.Lcd.fillRect(0,0,320,50,room_bg);
  M5.Lcd.setFreeFont(FMB18);
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setCursor((320 - M5.Lcd.textWidth(room_name)) / 2, 32);
  M5.Lcd.print(room_name); 
  // drawing verticle line
  M5.Lcd.drawFastVLine(150,50,190,TFT_DARKGREEN);
  // drawing horizontal line
  M5.Lcd.drawFastHLine(150,140,320,TFT_DARKGREEN);
}

/*-------------------------------------------------------------------------------*/
/* Function void tft_display_sensor_battery(int battery)                         */
/*                                                                               */
/* TASK    : show tft display sensor battery                                     */
/* UPDATE  : 22.09.2020                                                          */
/*-------------------------------------------------------------------------------*/
void tft_display_sensor_battery(int battery) 
{ 
  // setting the battery power
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setFreeFont(FMB9);
  M5.Lcd.drawString("Battery",200,160);
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setFreeFont(FMB18);
  M5.Lcd.drawNumber(battery,200,190);
  M5.Lcd.setFreeFont(FMB12);
  M5.Lcd.drawString("%",280,190);
}

/*-------------------------------------------------------------------------------*/
/* Function void tft_display_sensor_GPS(int battery)                         */
/*                                                                               */
/* TASK    : show tft display sensor battery                                     */
/* UPDATE  : 22.09.2020                                                          */
/*-------------------------------------------------------------------------------*/
void tft_display_sensor_GPS(String longitude, String latitude,String altitude, String sat, String date ,String hdop, String time)
{ 
  M5.Lcd.fillRect(0,150,145,220,TFT_WHITE);
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setFreeFont(FMB9);
  M5.Lcd.drawString("GPS",50,60);
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setFreeFont(FMB9);
  M5.Lcd.drawString("long:"+longitude,0,80);
  M5.Lcd.setFreeFont(FMB9);
  M5.Lcd.drawString("lat:"+latitude,0,100);
  M5.Lcd.setFreeFont(FMB9);
  M5.Lcd.drawString("alt:"+altitude,0,120);
  M5.Lcd.setFreeFont(FMB9);
  M5.Lcd.drawString("sat:"+sat,0,140);
  M5.Lcd.setFreeFont(FMB9);
  M5.Lcd.drawString("date: ",0,160);
  M5.Lcd.setFreeFont(FMB9);
  M5.Lcd.drawString(date,0,180);
  M5.Lcd.setFreeFont(FMB9);
  M5.Lcd.drawString("time:" + time, 0, 200);
  M5.Lcd.setFreeFont(FMB9);
  M5.Lcd.drawString("hdop: " + hdop,0,220);
}

void printInt(int x,int y ,int w, int h,unsigned long val, int len){
  M5.Lcd.fillRect(x,y,w,h,TFT_WHITE);
  char sz[32] = "*****************";
  sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i = strlen(sz); i < len; ++i) sz[i] = ' ';
  if (len > 0) sz[len - 1] = ' ';
  M5.Lcd.setFreeFont(FMB9);
  M5.Lcd.drawString(sz,x,y);
  smartDelay(0);
}

void printFloat(int x, int y ,int w, int h ,float val, int len, int prec) {
    M5.Lcd.fillRect(x , y, w, h,TFT_WHITE);
    M5.Lcd.drawString(String(val),x,y);
    int vi   = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1);  // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i = flen; i < len; ++i) M5.Lcd.drawString(" ",x,y);
    smartDelay(0);
}


void printDate(int x,int y ,int w, int h ,TinyGPSDate &d) {
    if (!d.isValid()) {
      M5.Lcd.fillRect(x , y, w, h,TFT_WHITE);
      M5.Lcd.drawString("**/**/****",x,y);
    } else {
        char sz[32];
        sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
        M5.Lcd.fillRect(x , y, w, h,TFT_WHITE);
        M5.Lcd.drawString(sz,x,y);
    }
    smartDelay(0);
}

void printTime(int x,int y ,int w, int h , TinyGPSTime &t) {
    if (!t.isValid()) {
        M5.Lcd.fillRect(x , y, w, h,TFT_WHITE);
        M5.Lcd.drawString("**:**:**",x,y);
    } else {
        char sz[32];
        sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
        M5.Lcd.fillRect(x , y, w, h,TFT_WHITE);
        M5.Lcd.drawString(sz,x,y);
    }
    smartDelay(0);
}


/*-------------------------------------------------------------------------------*/
/* Function void tft_display_sensor_battery(int battery)                         */
/*                                                                               */
/* TASK    : show tft display sensor battery                                     */
/* UPDATE  : 22.09.2020                                                          */
/*-------------------------------------------------------------------------------*/
void tft_display_sensor_Lora(short rssi,float snr,int boucle){
  M5.Lcd.fillRect(155,50,160,90,TFT_WHITE);
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setFreeFont(FMB9);
  M5.Lcd.drawString("Lora",190,50);
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setFreeFont(FMB9);
  M5.Lcd.drawString("RSSI: " + String(rssi),180,70);
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setFreeFont(FMB9);
  M5.Lcd.drawString("Success N: " + String(boucle),160,90);
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setFreeFont(FMB9);
  M5.Lcd.drawString("SNR: " + String(snr),160,110);
}
/*-------------------------------------------------------------------------------*/
/* Function void tft_display_update_battery(int battery)                         */
/*                                                                               */
/* TASK    : show tft display update heating                                     */
/* UPDATE  : 22.09.2020                                                          */
/*-------------------------------------------------------------------------------*/
void tft_display_update_battery(int battery)
{
  // setting the battery
  M5.Lcd.fillRect(160,190,105,30,TFT_WHITE);
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setFreeFont(FMB18);
  M5.Lcd.drawNumber(battery,200,190);
}

/*-------------------------------------------------------------------------------*/
/* Function void tft_display_m5stack(void)                                       */
/*                                                                               */
/* TASK    : show tft display m5stack (this m5stack)                             */
/* UPDATE  : 10.12.2020                                                          */
/*-------------------------------------------------------------------------------*/
void tft_display_m5stack(void)
{
    bat = M5.Power.getBatteryLevel();
    // display room screen
    tft_display_room_screen(room_screen,INFRABEL);
    // display battery sensor
    tft_display_sensor_battery(bat);
    //display info gps
    tft_display_sensor_GPS("0","0","0","0","**/**/****","0","**:**:**");
}

void initDisplay(void){
  tft_display_m5stack();
}