#include <EEPROM.h>
#include <LiquidCrystal.h>
#include "Menu.h"
#include "TimeDate.h"
#include "Temp.h"
#include "GetStored.h"
#include "Switch.h"
#include "Logging.h"


Timer T2;
int Debug_Bulb_pin = 17 ;
String ReqData= "analysis";

bool debugg(LiquidCrystal &);
String ReadData();
void analysis(LiquidCrystal &);
void DebuggRoutine(LiquidCrystal &);
int ReadVal();
void EEPROM_Debugg();
void Values_Debugg();
void Function_Debugg(LiquidCrystal &);
bool SecurityCheck();
int Read1DigitVal();
int ReadNum();
void Trigger_Bulb(bool);

bool debugg(LiquidCrystal &lcd)
  {
  if(Serial.available()>0){
    if(ReadData().equals(ReqData)){
      if (SecurityCheck()){
        analysis(lcd); 
        return true;}
    else return false;
    }
   }
  }
bool SecurityCheck()
  {
  Serial.println("Authorised Persons Only");
  Serial.println("Enter the Pass cose");
  T2.startTimer(10000);
  while(Serial.available()==0){if (T2.isTimerReady())break;}
  if(ReadData().equals("MyIncubator"))return true;
  else return false;
  }

String ReadData()
  {
   return Serial.readString();
  }

void analysis(LiquidCrystal &lcd)
  {
  while(true)
    {
    Serial.println("Choose a number to select between Operations");
    Serial.println("0:- EEprom 1:- function 2:- Values 3:- Exit");
    int val = Read1DigitVal();
    if(val=='0'){EEPROM_Debugg();}
    else if(val=='1'){Function_Debugg(lcd);}
    else if(val=='2'){Values_Debugg();}
    else if(val == '3'){break;}
    else{Serial.println("Invalid input");};
    }  
  }

void EEPROM_Debugg()
  {
  Serial.println("Choose a number to select between various adresses");
  Serial.println("0 - Set date, 1 - Set Month, 2-Egg type, 3- Stop day for custom");
  int val = Read1DigitVal();
  switch(val)
    {
    case '0':
    Serial.println("Enter the Date");
    EEPROM.update(0,ReadNum()); 
    break;  
    case '1':
    Serial.println("Enter the Month");
    EEPROM.update(1,ReadNum());
    break; 
    case '2':
    Serial.println("Enter the Egg Type");
    EEPROM.update(2,Read1DigitVal()-48);
    break;
    case '3':
    Serial.println("Enter the Stop Day");
    EEPROM.update(3,ReadNum());
    break;    
    }
  }

void Values_Debugg()
  {
  Serial.println("Choose a number to select between various values");
  Serial.println("0- Temperature, 1 - Date, 2- Month, 3- Year, 4- Hour, 5- Minute");
  int val = Read1DigitVal();
  switch(val)
    {
    case '0':
    Serial.println("Enter the Tenperature");
    temp=ReadNum();
    break;  
    case '1':
    Serial.println("Enter the Date");
    Date=ReadNum();
    break; 
    case '2':
    Serial.println("Enter the Month");
    Month=ReadNum();
    break;
    case '3':
    Serial.println("Enter the Year");
    Year=ReadNum();
    break;
    case '4':
    Serial.println("Enter the Hour");
    Hour=ReadNum();
    break;
    case '5':
    Serial.println("Enter the Minute");
    Min=ReadNum();
    break;    
    }  
  }

void Function_Debugg(LiquidCrystal &lcd)
  {
  Serial.println("Choose a number to select various Function to execute");
  Serial.println("0- Ventilation Fan, 1- Rotate Egg, 2- Circulating fan, 3- Heating bulb, 4:- Log_DATA, 5:- Run the Debug Routine");
  int val = Read1DigitVal();
  switch(val)
    {
    case '0':
    Serial.println("Choose an option");
    Serial.println("0:- slow seed, 1:- High speed");
    val = Read1DigitVal();
    if(val=='1')ventilationFan(HIGH);
    else ventilationFan(LOW);
    break;  
    case '1':
    Serial.println("Enter the seconds to rotate in millisecond");
    rotate_mainmotor(ReadNum());
    break; 
    case '2':
    Serial.println("Enter the PWM value");
    PulseCirculatingFan(ReadNum());
    break; 
    case '3':
    Serial.println("Choose an option");
    Serial.println("0:- OFF, 1:- ON");
    val = Read1DigitVal();
    if(val=='1')Trigger_Bulb(HIGH);
    else Trigger_Bulb(LOW);
    break; 
    case '4':
    Log_EEPROM();
    Variable_values();
    break; 
    case '5':
    DebuggRoutine(lcd);
    break;    
    }   
  }

void DebuggRoutine(LiquidCrystal &Main_lcd)
  {
  Read_EEPROM();
  Log_EEPROM();
  while(true)
    {  
    timedate_Display(Main_lcd);
    period(Main_lcd);
    TEMP_Functions(Main_lcd); 
    Switch_Eggtype(); 
    Log_values();
    if(Serial.available()>0){if(ReadData().equals("Stop"))break;}
    }  
  }


int ReadNum()
  {
  while(Serial.available()==0);
  return(ReadData().toInt());
  }

void Trigger_Bulb(bool State)
  {
  digitalWrite(Debug_Bulb_pin,State);  
  }

int Read1DigitVal()
  {
  while(Serial.available()==0);
  return(Serial.read());  
  }
