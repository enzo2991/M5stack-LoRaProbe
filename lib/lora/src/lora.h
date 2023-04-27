#ifndef LORA_H
#define LORA_H
    extern bool sending;
    extern short rssi;
    extern float snr;
    void initLora();
    void sendPayLoad(float lat,float lng,float alt,int hdop,int sat);
#endif