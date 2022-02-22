// include the library code:
#include <LiquidCrystal.h>
#include "Menu.h"
#include "TimeDate.h"
#include "Temp.h"
#include "GetStored.h"
#include "Switch.h"
#include "Logging.h"
#include "Debugg.h"

LiquidCrystal Main_lcd(5,6,7,8,9,10);  // initialize the library with the numbers of the interface pins
                 /*eeprom has adress 0 as the date of setiing ,1 as the month of setting, 2 for type of egg(hen or duck)
                          adress 3 for custom incubation stop day
                // e.g. 7:32:16 | Monday October 31, 2016: */
//                rtc.setTime(16, 32, 7, 2, 31, 10, 16);              

Timer t1,t2,t3;
          
void setup() { 
  Main_lcd.begin(16, 2);     
  Serial.begin(9600);
  rtc.begin();   //you can use the rtc.setTime(s, m, h, day, date, month, year) eg : rtc.setTime(30, 02, 11, 3, 4, 6, 19);
  pinMode(LED_BUILTIN, OUTPUT);    //Connected to Pin 13
  pinMode(motorpin, OUTPUT);       //Connected to Pin 15
  pinMode(pwmpin_fan,OUTPUT);      //connected to Pin 11
  pinMode(HighTempLed, OUTPUT);     //Connected to Pin 16
  pinMode(Debug_Bulb_pin, OUTPUT);  //Connected to Pin 17
  pinMode(fanpin,OUTPUT);           //Connected to Pin 14
  pinMode(setpin,INPUT);            //Connected to Pin 2
  pinMode(incpin,INPUT);            //Connected to Pin 3
  pinMode(decpin,INPUT);            //Connected to Pin 4   
  attachInterrupt(digitalPinToInterrupt(setpin), change_set_flag, HIGH);          //DHT pin connected to 12
  attachInterrupt(digitalPinToInterrupt(incpin), change_increment_flag, HIGH);
  Read_EEPROM();
  Log_EEPROM();
  t1.startTimer(100);
  t2.startTimer(200);
  t3.startTimer(300);
}

void loop() { 
  if(t1.isTimerReady())
      {timedate_updateval();
      timedate_Display(Main_lcd);
      t1.startTimer(300);}
  checkReset(Main_lcd);
  if(t2.isTimerReady()){period(Main_lcd);t2.startTimer(10000);}
  if(t3.isTimerReady())
    {Update_Temp();
    TEMP_Functions(Main_lcd);t2.startTimer(600);} 
  Switch_Eggtype(); 
  Log_values();
//  if(debugg(Main_lcd))Read_EEPROM();;
 }





 
