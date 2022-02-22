#ifndef _TIMEDATE_H_
#define _TIMEDATE_H_

#include"GetStored.h"


#include <SparkFunDS1307RTC.h>
#include <Wire.h>
#include <LiquidCrystal.h>

int Day, Hour, Min, Date, Sec, Month,Year;  //variables for date and time
int incubation_period;
                             
void timedate_Display(LiquidCrystal&);                                      //function to display the time and date                                                                    from RTC1307
void timedate_updateval();     //function to update value from RTC1307
int getminute();                                                            //function to return the current minute
int gethour();
int getdate();                                                              //function to return the date
int getmonth();                                                             //function to return the month
void period(LiquidCrystal&);                                                //function to calculate period
void period_display(LiquidCrystal&);                                    //function to display the period
int getNumDays(int );

void timedate_Display(LiquidCrystal &lcd)
  {
  lcd.setCursor(0, 1);
  lcd.print(Date);
  lcd.print("/");
  lcd.print(Month);
  lcd.print("/");
  lcd.print(Year);
  lcd.setCursor(13,0);
  lcd.print(",");
  lcd.print(Sec);
  lcd.print(" ");
  }

int getminute(){return Min;}
int getdate(){return Date;}
int getmonth(){return Month;}
int gethour(){return Hour;}

void timedate_updateval()
  {
  rtc.update();
  rtc.set24Hour();
  Date = rtc.date();
  Hour = rtc.hour();
  Day = rtc.day();
  Min = rtc.minute();
  Sec = rtc.second();
  Month = rtc.month();   
  Year = rtc.year(); 
  }

void period(LiquidCrystal &lcd)
  {
  if (SetMonth==Month)
    {
    incubation_period=((Date-SetDate));
    }
  else
    incubation_period=(getNumDays(SetMonth)-SetDate)+Date;
    period_display(lcd);
 }

 void period_display(LiquidCrystal &lcd)
  {
  lcd.setCursor(0,0);
  lcd.print("Total Days:");
  lcd.print(incubation_period);
  }

 int getNumDays(int Month)
  {
  if (Month == 4 || Month == 6 || Month == 9 || Month == 11)return 30;   
  else if (Month == 02)
    {
    bool leapyear = (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
    if (leapyear == 0)return 28;
    else return 29;
    }
  else 
    return 31;
  }
#endif
