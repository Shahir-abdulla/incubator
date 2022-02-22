#ifndef _EGG_H_
#define _EGG_H_
          
class Egg{
  int Stop_rotation_day;
  public:
  Egg(int stop_day)
    {Stop_rotation_day = stop_day;}  

  int Get_StopRotationDay()
    {return(Stop_rotation_day);}

  bool isRotationDay(int incubation_period)
    {return(incubation_period < Stop_rotation_day);}  

};

#endif
