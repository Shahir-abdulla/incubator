#include "temperature_sensor.h"
#include "RTC.h"
#include "oled_display.h"

void setup()
{
  Serial.begin(9600);
  init_rtc();
  init_display();
}

void loop()
{
  get_temp();
  get_date();
  show_elements();
}
