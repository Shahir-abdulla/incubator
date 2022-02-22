#ifndef _GETSTORED_H_
#define _GETSTORED_H_


#include<EEPROM.h>

int EggType;
int SetDate;
int SetMonth;
int CustomStopDay;

void Read_EEPROM()
  {
  SetDate = EEPROM.read(0);
  SetMonth = EEPROM.read(1);
  EggType = EEPROM.read(2);  
  CustomStopDay = EEPROM.read(3);
  }

#endif
