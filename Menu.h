#ifndef _MENU_H_
#define _MENU_H_

#include<EEPROM.h>
#include <LiquidCrystal.h>
#include "TimeDate.h"
#include "GetStored.h"

volatile bool set_flag=0;
volatile bool increment_flag=0;

int incpin=3; //pin for choosing hen or duck
int decpin=4;   //pin for selecting the option choosen
int setpin=2;  //pin for reseting the incubator

void menu(LiquidCrystal&);
void custom(LiquidCrystal&);
int counter(LiquidCrystal&);
void checkReset(LiquidCrystal&);

void change_set_flag()
  {
  if (!set_flag)
  set_flag  = HIGH;
   }

void change_increment_flag()
  {
  if(!increment_flag)
  increment_flag = HIGH;
  }

void checkReset(LiquidCrystal &lcd)
  {
  if (set_flag)
    {
    lcd.clear();
    lcd.print("Press set button");
    lcd.setCursor(0,1);
    lcd.print("again to reset");
    Serial.println("Press the set button again to reset");
    set_flag=LOW;
    delay(2000);
    if (set_flag)
        {
        set_flag = 0;
        menu(lcd);
        }
    set_flag = LOW;
    lcd.clear();
    Read_EEPROM();   
   } 
  }

void menu(LiquidCrystal &lcd)
  {
  lcd.clear();
  lcd.print("Incubator Reset");
  Serial.println("incubator Reset");
  delay(2000);
  int Date = getdate();
  int Month = getmonth();
  EEPROM.update(0,rtc.date());
  EEPROM.update(1,rtc.month());
  byte arrow[8]={B00010,B00110,B01110,B11110,B01110,B00110,B00010,B00000};
  lcd.createChar(0,arrow);
  lcd.clear();
  lcd.print("choose 1 option");
  delay(1000);
  int option_value=0;
  while(true)
    {
    if(increment_flag){option_value++;increment_flag = LOW;}
    else if(digitalRead(decpin)==HIGH)option_value--;
    if(option_value>=5)option_value=0;
    if (option_value < 2)
        {  
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("CHICKEN EGG");
        lcd.setCursor(0,1);
        lcd.print("DUCK EGG   ");
        if(option_value==0){lcd.setCursor(13,0);lcd.write(0);lcd.setCursor(13,1);lcd.print("  ");}     
        else if(option_value==1){lcd.setCursor(13,1);lcd.write(0);lcd.setCursor(13,0);lcd.print("  ");}
        }
    else if (option_value >= 2  && option_value < 4)
        {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("QUIL EGG");
        lcd.setCursor(0,1);
        lcd.print("PEAHEN EGG");
        if(option_value==2){lcd.setCursor(13,0);lcd.write(0);lcd.setCursor(13,1);lcd.print("  ");}     
        else if(option_value==3){lcd.setCursor(13,1);lcd.write(0);lcd.setCursor(13,0);lcd.print("  ");}
        }
    else if (option_value==4)
      {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("CUSTOMISE"); 
      lcd.setCursor(13,0);
      lcd.write(0);
      }
    else 
      {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Press the option button");
      }
    delay(500);
    if(set_flag){break;}
    }
   if (option_value==1)
    { 
    EEPROM.update(2,2);
    lcd.clear();
    lcd.print("duck egg set");
    }
  else if (option_value==2)
    {
    EEPROM.update(2,3);
    lcd.clear();
    lcd.print("quil egg set");
    }
  else if(option_value==3)
    {
    EEPROM.update(2,4);
    lcd.clear();
    lcd.print("peahen egg set");
    }
  else if(option_value==4)
    {
    EEPROM.update(2,5);
    lcd.clear();
    lcd.print("CUSTM OPTION SET");
    custom(lcd);
    }
  else
    {
    EEPROM.update(2,1);
    lcd.clear();
    lcd.print("chicken egg set");
    }
  delay(2000);
  set_flag=0;
  lcd.clear();
 }

void custom(LiquidCrystal &lcd)
  {
  int sum=0,total=0;
  while(true)
    {
    lcd.clear();
    lcd.print("Specify day to");
    lcd.setCursor(0,1);
    lcd.print("stop rotation");
    set_flag=0;
    delay(1000);
    if (set_flag)
      {
      sum = counter(lcd);
      break;
      }
    }   
  EEPROM.update(3,sum);
  }


int counter(LiquidCrystal &lcd)
  {
  int sum=0;
  while(true)
    {
    lcd.clear();
    lcd.setCursor(8,0);
    lcd.print(sum);
    delay(100);
    if(digitalRead(incpin))
      sum++;
    if(digitalRead(setpin))
      break;
    if(digitalRead(decpin))
      sum--;
   }
  return sum;
 }

#endif
