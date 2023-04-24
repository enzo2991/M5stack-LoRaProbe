#include <Arduino.h>
#include <M5Stack.h>
#include <TinyGPS++.h>
#include <display.h>
#include <TimeLib.h>
#include <lora.h>
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
HardwareSerial ss(2);
tmElements_t it_time;
time_t unix_timestamp;
double lat, lng, alt, last_lat,last_lng;
int sat, hdop,datevalue;
unsigned long distanceToLast;

unsigned long distanceMin = 20;
TinyGPSDate date;
TinyGPSTime inTime;

 void gpsinit(){
    ss.begin(GPSBaud,SERIAL_8N1,13,1);
 };

// This custom version of delay() ensures that the gps object
// is being "fed".
void smartDelay(unsigned long ms) {
    unsigned long start = millis();
    do {
        while (ss.available()) gps.encode(ss.read());
    } while (millis() - start < ms);
}

void printScreen(){
    printInt(45,140,50,15,sat, 5);
    printInt(50,220,50,15,hdop, 5);
    printFloat(45, 100, 50,15,lat, 11, 6);
    printFloat(55, 80, 50, 15,lng, 12, 6);
    printDate(0,180,120,15 ,date);
    printTime(55,200,95,15 ,inTime);
    printFloat(45,120,90,15,alt, 7, 2);
}

void gpsgetdata(){
    (gps.satellites.isValid()) ? sat = gps.satellites.value(): sat;
    (gps.hdop.isValid()) ? hdop = gps.hdop.value(): hdop;
    (gps.altitude.isValid()) ? alt = gps.altitude.value(): alt;
    if(gps.location.isValid()){
        lat = gps.location.lat();
        lng = gps.location.lng();
        distanceToLast = (unsigned long)TinyGPSPlus::distanceBetween(lat, lng, last_lat, last_lng);
    } else {
        lat;
        lng;
        distanceToLast;
    }
    if(gps.date.isValid()){
        date = gps.date;
        it_time.Day = date.day();
        it_time.Month = date.month() - 1;
        it_time.Year = date.year() - 1970;
    }
    if(gps.time.isValid()){
        inTime = gps.time;
        it_time.Second = inTime.second();
        it_time.Minute = inTime.minute();
        it_time.Hour = inTime.hour();
    }
    if(gps.time.isValid() && gps.date.isValid()){
        unix_timestamp = makeTime(it_time);
    }
    printScreen();
    if(distanceToLast > distanceMin)
     {
      sendPayLoad(lat,lng,alt,hdop,sat);
     }

    last_lat = lat;
    last_lng = lng;

    smartDelay(1000);

    if (millis() > 5000 && gps.charsProcessed() < 10)
        M5.Lcd.println(F("No GPS data received: check wiring"));
}


