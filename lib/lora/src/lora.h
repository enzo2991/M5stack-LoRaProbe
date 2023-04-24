#ifndef LORA_H
#define LORA_H
    extern bool sending;
    void initLora();
    void sendPayLoad(float lat,float lng,float alt,int hdop,int sat);
#endif