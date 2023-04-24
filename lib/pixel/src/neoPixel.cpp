#include <M5Stack.h>
#include <Adafruit_NeoPixel.h>
#define M5STACK_FIRE_NEO_NUM_LEDS 10
#define M5STACK_FIRE_NEO_DATA_PIN 15
bool tft_backlight = true;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(M5STACK_FIRE_NEO_NUM_LEDS, M5STACK_FIRE_NEO_DATA_PIN, NEO_GRB + NEO_KHZ800);


/*-------------------------------------------------------------------------------*/
/* Function void rgb_neopixel(String color)                                      */
/*                                                                               */
/* TASK    : show rgb neopixels (co2 ampel)                                      */
/* UPDATE  : 07.10.2020                                                          */
/*-------------------------------------------------------------------------------*/
void rgb_neopixel(int r,int g,int b)
{
  // right side
  if (tft_backlight == true)
  {
    pixels.setPixelColor(0, pixels.Color(r,g,b));
    pixels.show(); delay(200);
    pixels.setPixelColor(1, pixels.Color(r,g,b));
    pixels.show(); delay(200);
    pixels.setPixelColor(2, pixels.Color(r,g,b));
    pixels.show(); delay(200);
    pixels.setPixelColor(3, pixels.Color(r,g,b));
    pixels.show(); delay(200);
    pixels.setPixelColor(4, pixels.Color(r,g,b));
    pixels.show(); delay(200);
    // left side
    pixels.setPixelColor(5, pixels.Color(r,g,b));
    pixels.show(); delay(200);
    pixels.setPixelColor(6, pixels.Color(r,g,b));
    pixels.show(); delay(200);
    pixels.setPixelColor(7, pixels.Color(r,g,b));
    pixels.show(); delay(200);
    pixels.setPixelColor(8, pixels.Color(r,g,b));
    pixels.show(); delay(200);
    pixels.setPixelColor(9, pixels.Color(r,g,b));
    pixels.show(); delay(200);
  }
}

/*-------------------------------------------------------------------------------*/
/* Function void rgb_neopixel_on(String color)                                   */
/*                                                                               */
/* TASK    : show rgb neopixels immediately                                      */
/* UPDATE  : 07.10.2020                                                          */
/*-------------------------------------------------------------------------------*/
void rgb_neopixel_on(int r,int g,int b)
{
  // right side
  pixels.setPixelColor(0, pixels.Color(r,g,b));
  pixels.setPixelColor(1, pixels.Color(r,g,b));
  pixels.setPixelColor(2, pixels.Color(r,g,b));
  pixels.setPixelColor(3, pixels.Color(r,g,b));
  pixels.setPixelColor(4, pixels.Color(r,g,b));
  // left side
  pixels.setPixelColor(5, pixels.Color(r,g,b));
  pixels.setPixelColor(6, pixels.Color(r,g,b));
  pixels.setPixelColor(7, pixels.Color(r,g,b));
  pixels.setPixelColor(8, pixels.Color(r,g,b));
  pixels.setPixelColor(9, pixels.Color(r,g,b));
  pixels.show();
}

/*-------------------------------------------------------------------------------*/
/* Function void rgb_neopixel_off()                                              */
/*                                                                               */
/* TASK    : rgb neopixels off                                                   */
/* UPDATE  : 18.11.2020                                                          */
/*-------------------------------------------------------------------------------*/
void rgb_neopixel_off()
{
  // right side
  pixels.setPixelColor(0, pixels.Color(0,0,0));
  pixels.setPixelColor(1, pixels.Color(0,0,0));
  pixels.setPixelColor(2, pixels.Color(0,0,0));
  pixels.setPixelColor(3, pixels.Color(0,0,0));
  pixels.setPixelColor(4, pixels.Color(0,0,0));
  // left side
  pixels.setPixelColor(5, pixels.Color(0,0,0));
  pixels.setPixelColor(6, pixels.Color(0,0,0));
  pixels.setPixelColor(7, pixels.Color(0,0,0));
  pixels.setPixelColor(8, pixels.Color(0,0,0));
  pixels.setPixelColor(9, pixels.Color(0,0,0));
  pixels.show();
}

/*-------------------------------------------------------------------------------*/
/* Function void initPixels()                                                    */
/*                                                                               */
/* TASK    :     activate the NeoPixels                                          */
/* UPDATE  : 07.10.2020                                                          */
/*-------------------------------------------------------------------------------*/
void initPixels()
{
  pixels.begin();
  rgb_neopixel(0,0,0);
}