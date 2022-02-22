#ifndef _SWITCH_H_
#define _SWITCH_H_
#include "Egg.h"
#include "TimeDate.h"
#include "GetStored.h"

int motorpin = 15; //connet the egg rotating motor
int fanpin=14; //pin for relay for Upper fan to control the inlet of fresh air
               //this will be made to rotate faster from the day stop_rotation
int RotateMotorAt = 20;
bool Flag1_MainMotor,Flag2_MainMotor,Flag3_MainMotor;
bool isFanFast;

void Switch_Eggtype();
void rotate_mainmotor(int Delaytime=150);
void ventilationFan(bool);
void hen();
void duck();
void quil();
void Custom();
void Rotate();
void SetFlags();


void Switch_Eggtype()
  {  

  switch (EggType)
    {
    case 1:
      hen();
      break;
    case 2:
      duck();
      break;
    case 3:
      quil();
      break;
    case 4:           //the time for peahen and duck is same and hence duck() can be called or executed
       duck();
       break;
    case 5:
        Custom();
        break;
    default:
       hen();
       break;
    }
   SetFlags();
   Rotate();  
  }

void hen()
  {
  Egg hen(19);
  Flag1_MainMotor = (hen.isRotationDay(incubation_period)); 
  }

void duck()
  {
  Egg duck(26);
  Flag1_MainMotor = (duck.isRotationDay(incubation_period)); 
  }

void quil()
  {
  Egg quil(15);
  Flag1_MainMotor = (quil.isRotationDay(incubation_period)); 
  }

void Custom()
  {
  Egg Custom(CustomStopDay);
  Flag1_MainMotor = (Custom.isRotationDay(incubation_period)); 
  }

void SetFlags()
  {
   if (getminute() ==  RotateMotorAt && (gethour()%2 ==0)){Flag3_MainMotor =1;}
   if (getminute() !=  RotateMotorAt){Flag2_MainMotor = 1;Flag3_MainMotor = 0;}
  }

void Rotate()
  {
  if (Flag1_MainMotor && Flag2_MainMotor && Flag3_MainMotor){rotate_mainmotor();Flag2_MainMotor=0;} 
  ventilationFan(!Flag1_MainMotor);   
  }

void rotate_mainmotor(int Delaytime)
  {
  digitalWrite(motorpin,HIGH);
  delay(Delaytime);
  digitalWrite(motorpin,LOW);
  }
 
void ventilationFan(bool state)
  {
  digitalWrite(fanpin, state); 
  isFanFast=state;
  }


#endif
