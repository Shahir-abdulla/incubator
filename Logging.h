#ifndef _LOGGING_H_
#define _LOGGING_H_

#include "GetStored.h"
#include "Temp.h"
#include "TimeDate.h"
#include "Switch.h"
#include "Timer.h"

/*
 * 
Log_EEPROM();
Type of Egg : ----
Date of Setting :---
Month of Setting : ----
Stop day for Custom Egg : ----


Log_Variables()
Temperature : ----
Date and Time : ----
Total Days of incubation :  ----
Is ventilation Fan Fast : ----
Main Fan Rotation Speed: ----
Minute of next Egg Rotation : ----
*/
Timer T1;


void Log_values();
void Log_EEPROM();
void Variable_values();

void Log_values()
  {
  if(T1.isTimerReady())
    {
     Variable_values();
     T1.startTimer(1000); 
    }  
  }

void Log_EEPROM()
  {
  Serial.print("Type of EGG : ");Serial.println(EggType);
  Serial.print("Date of Setting : ");Serial.println(SetDate);
  Serial.print("Month of Setting : ");Serial.println(SetMonth);
  Serial.print("Stop day for custom Egg : ");Serial.println(CustomStopDay);
  Serial.println("----------------------------------------------------------------------------");
  T1.startTimer(3000);
  }

void Variable_values()
  {
  Serial.print("Temperature : ");Serial.println(temp);
  Serial.print("Date and Time : ");Serial.print(Date);Serial.print("/");Serial.print(Month);Serial.print("/");Serial.print(Year);Serial.print("  ");Serial.print(Hour);Serial.print(":");Serial.print(Min);Serial.print(":");Serial.println(Sec); 
  Serial.print("Total Days of incubation : ");Serial.println(incubation_period);
  Serial.print("Is ventilation Fan Fast : ");Serial.println(isFanFast);
  Serial.print("Main Fan Rotation Speed: ");Serial.println(MainFanSpeed);
  Serial.print("Minute of next Egg Rotation : ");Serial.println(RotateMotorAt);
  Serial.println("----------------------------------------------------------------------------");
  }

#endif
