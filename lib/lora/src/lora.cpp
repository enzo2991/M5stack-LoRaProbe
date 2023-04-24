
#include <M5Stack.h>
#include <Arduino.h>
#include <neoPixel.h>
#include <CayenneLPP.h>
#include <gps.h>
#define BUFFER_LENGTH_MAX    256
#define LENGTH_BYTE 60
bool sending = false;
char* DevEui="a8610a32374f7508";
char* AppEui="8899AABBCCDDEEFF";   
char* AppKey="7FF7005D07BFCD15AC5793AFA7BB5CAF";
char _buffer[256];
CayenneLPP lpp(LENGTH_BYTE);

/*-------------------------------------------------------------------------------*/
/* Function bool ReceiveAT(uint32_t timeout)                                     */
/*                                                                               */
/* TASK    : receive AT msg's from the M5Stack COM.LoRaWAN Module                */
/* UPDATE  : 24.01.2021                                                          */
/*-------------------------------------------------------------------------------*/
bool ReceiveAT(uint32_t timeout)
{
  uint32_t nowtime = millis();
  while(millis() - nowtime < timeout){
    if (Serial1.available() !=0) {
      String str = Serial2.readString();
      if (str.indexOf("+OK") != -1 || str.indexOf("+ERROR") != -1) {
        Serial.println(str);
        return true;
      }else {
        Serial.println("[!] Syntax Error");
        break;
      }
    }
  }
  Serial.println("[!] Timeout");
  return false;
}

/*-------------------------------------------------------------------------------*/
/* Function void ATCommand(char cmd[],char date[], uint32_t timeout = 50)        */
/*                                                                               */
/* TASK    : send AT commands to the M5Stack COM.LoRaWAN Module                  */
/* UPDATE  : 24.01.2021                                                          */
/*-------------------------------------------------------------------------------*/
void ATCommand(char cmd[],char date[], uint32_t timeout = 50)
{
  char buf[256] = {0};
  if(date == NULL)
  {
    sprintf(buf,"AT+%s",cmd);
  }
  else
  {
    sprintf(buf,"AT+%s=%s",cmd,date);
  }
  Serial1.write(buf);
  delay(200);
  ReceiveAT(timeout);
}


//read buffer
short readBuffer(char *buffer, int length, uint32_t timeout)
{
  short i = 0;
  unsigned long timerStart, timerEnd;

  timerStart = millis();

  while (1)
  {
    if (i < length)
    {
      while (Serial1.available())
      {
        char c = Serial1.read();
        buffer[i ++] = c;
      }
    }

    timerEnd = millis();
    if (timerEnd - timerStart > timeout)break;
  }

  return i;
}

//Transfer Packet
bool transferPacket(unsigned char *buffer, int length, uint32_t timeout)
{
  //1. array to string
  char str[LENGTH_BYTE] = "";
  {
    for (unsigned int i = 0; i < length; i++)
    {
      byte nib1 = (buffer[i] >> 4) & 0x0F;
      byte nib2 = (buffer[i] >> 0) & 0x0F;
      str[i * 2 + 0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
      str[i * 2 + 1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
    }
    str[length * 2] = '\0';
  }

  //2. send
  char buf[256] = {0};
  while (Serial1.available())Serial1.read();
  ATCommand("SendHex", str);

  Serial1.write(buf);
  memset(_buffer, 0, BUFFER_LENGTH_MAX);
  readBuffer(_buffer, BUFFER_LENGTH_MAX, timeout);
  if (strstr(_buffer, "sending"))return true;
  return false;
}

void initLora(){
  Serial1.begin(115200, SERIAL_8N1, 5, 0);
  ATCommand("LORAWAN", "?");
  delay(500);
  ATCommand("LORAWAN", "1");
  delay(500);

  // your TTN access data
  ATCommand("DevEui", DevEui);
  delay(500);
  // always the same for all devices
  ATCommand("AppEui", AppEui);
  delay(500);
  ATCommand("AppKey", AppKey);
  delay(500);

  Serial.println("Join=1");
  ATCommand("Join", "1");

  delay(2000);
}

void sendPayLoad(float lat,float lng,float alt,int hdop,int sat){
  sending = true;
  lpp.reset();
  bool result = false;

  // activate communication
  ATCommand("LoraSet", "?");
  delay(500);

  // actual battery level
  uint8_t bat = M5.Power.getBatteryLevel();
  // donnée lpp qui sont envoyer
  lpp.addPower(0,bat); // batterie
  lpp.addUnixTime(1,unix_timestamp); //heure 
  lpp.addSat(2,sat);
  lpp.addHdop(3,hdop);// hdop
  lpp.addGPS(4,lat,lng,alt); // position gps
  rgb_neopixel(0,0,255);
  result = transferPacket((unsigned char *)lpp.getBuffer(),lpp.getSize(),5000);
  if(result == true){
    rgb_neopixel(0,255,0);
  }else {
    rgb_neopixel(255,0,0);
  }
  rgb_neopixel_off();
  sending = false;
}
