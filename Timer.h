#ifndef _TIMER_H_
#define _TIMER_H_


class Timer {

  long timerStart = 0;
  long timerTarget = 0;

public:

  startTimer(int msec) {
    timerStart = millis();
    timerTarget = msec;
  }

  bool isTimerReady(){ 
    return (millis() - timerStart) > timerTarget;
  }

  
  int gettime(){
    return (millis() - timerStart);
  }

};


#endif // _TIMER_H_
