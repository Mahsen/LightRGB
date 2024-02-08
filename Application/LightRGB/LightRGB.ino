#include <ESP8266WiFi.h>
//---------------------------------------------------------------------------------
const int Pin_LED_CPU =          10; 

const int Pin_Red =              13; 
const int Pin_Green =            12; 
const int Pin_Blue =             14; 
const int PWM_Range =            256; 

const uint8_t HSVlights[61] = 
{0, 4, 8, 13, 17, 21, 25, 30, 34, 38, 42, 47, 51, 55, 59, 64, 68, 72, 76,
81, 85, 89, 93, 98, 102, 106, 110, 115, 119, 123, 127, 132, 136, 140, 144,
149, 153, 157, 161, 166, 170, 174, 178, 183, 187, 191, 195, 200, 204, 208,
212, 217, 221, 225, 229, 234, 238, 242, 246, 251, 255};
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Set_Value_LED_CPU(bool Value)
{
  digitalWrite(Pin_LED_CPU, Value?LOW:HIGH);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Set_Value_RGB(int Red, int Green, int Blue)
{
  analogWrite(Pin_Red, Red);
  analogWrite(Pin_Green, Green);
  analogWrite(Pin_Blue, Blue);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// the real HSV rainbow
void trueHSV(int angle)
{
  byte red, green, blue;

  if (angle<60) {red = 255; green = HSVlights[angle]; blue = 0;} else
  if (angle<120) {red = HSVlights[120-angle]; green = 255; blue = 0;} else 
  if (angle<180) {red = 0, green = 255; blue = HSVlights[angle-120];} else 
  if (angle<240) {red = 0, green = HSVlights[240-angle]; blue = 255;} else 
  if (angle<300) {red = HSVlights[angle-240], green = 0; blue = 255;} else 
                 {red = 255, green = 0; blue = HSVlights[360-angle];} 
  Set_Value_RGB(red, green, blue);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{

  ///
  //{
  pinMode(Pin_LED_CPU, OUTPUT);
  analogWriteRange(PWM_Range);
  //}
  
  Set_Value_LED_CPU(false);
  Set_Value_RGB(0, 0, 20);
  
  Serial.begin(115200);
  Serial.println();

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{

  for (int k=0; k<360; k++)
  {
    trueHSV(k);
    delay(100);
  }

}
