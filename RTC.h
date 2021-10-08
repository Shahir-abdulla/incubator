#include "RTClib.h"

RTC_DS3231 rtc;
DateTime now;

void init_rtc()
{
    if (!rtc.begin())
    {
        Serial.println("Couldn't find RTC");
        while (1)
            ;
    }

    rtc.adjust(DateTime(__DATE__, __TIME__));
}

void get_date()
{
    now = rtc.now();
    Serial.print("Date: ");
    char date[10] = "hh:mm:ss";
    Serial.println(now.toString(date));
}
