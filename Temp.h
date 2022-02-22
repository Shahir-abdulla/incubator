#ifndef _TEMP_H_
#define _TEMP_H_
#include <dht.h>
#include <LiquidCrystal.h>

#define DHT11_PIN 12
dht DHT; 

int pwmpin_fan=11;//variable to give pwm signal to the main fan
int temp;     // variable to store temperature
int temp_offset=-3; //variable to compensate for the error of temperature sensor  
int HighTempLed = 16;  //Connect to the Tmpertature indicating led
int MainFanSpeed;


void TEMP_Functions(LiquidCrystal &);
void Update_Temp();
void PulseCirculatingFan(int);
void display_temp(LiquidCrystal &);
void ToggleLed(int);
void CalcCirculatingFan();

void (* resetFunc)(void) = 0;

void TEMP_Functions(LiquidCrystal &lcd)
 {
 CalcCirculatingFan();
 PulseCirculatingFan(MainFanSpeed); 
 display_temp(lcd);
 ToggleLed(temp); 
}

void Update_Temp()
  {
  DHT.read11(DHT11_PIN);
  temp = DHT.temperature;
  temp = temp + temp_offset;  
  if(temp==0)resetFunc();
  }

void CalcCirculatingFan()
  {
  if(temp<36) MainFanSpeed=0;
  else if (temp >39) MainFanSpeed=255;  
  else MainFanSpeed=170;
  }

void PulseCirculatingFan(int analogVal)
  {
  analogWrite(pwmpin_fan,analogVal);  
  }

void display_temp(LiquidCrystal &lcd)
  {
  lcd.setCursor(9, 1);
  lcd.print("Temp");
  lcd.print(":");
  lcd.print(temp);
  }

void ToggleLed(int temperature)
  {
   if (temperature > 37)
    digitalWrite(HighTempLed, HIGH);
  if (temperature < 37)
    digitalWrite(HighTempLed, LOW);  
  }


#endif
