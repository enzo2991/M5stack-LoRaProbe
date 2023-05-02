#ifndef DISPLAY_H
#define DISPLAY_H
#include <TinyGPS++.h>
extern uint8_t bat;
void initDisplay();
void tft_display_m5stack();
void tft_display_sensor_GPS(String longitude, String latitude,String altitude, String sat, String date, String hdop, String time);
void printInt(int x,int y ,int w, int h,unsigned long val, int len);
void printFloat(int x, int y ,int w, int h ,float val, int len, int prec);
void printDate(int x,int y ,int w, int h ,TinyGPSDate &d);
void printTime(int x,int y ,int w, int h ,TinyGPSTime &t);
void tft_display_sensor_Lora(short rssi);
void tft_display_update_battery(int battery);
void fadeScreen();
void showScreen();
#endif