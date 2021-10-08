#include <OneWire.h>

OneWire ds(15);
float celsius;

void get_temp()
{
    byte i;
    byte present = 0;
    byte type_s;
    byte data[12];
    byte addr[8];
    //  float celsius, fahrenheit;

    if (!ds.search(addr))
    {
        //    Serial.println("No more addresses.");
        //    Serial.println();
        ds.reset_search();
        delay(250);
        return;
    }

    if (OneWire::crc8(addr, 7) != addr[7])
    {
        return;
    }

    ds.reset();
    ds.select(addr);
    ds.write(0x44, 1);

    delay(1000); // maybe 750ms is enough, maybe not

    present = ds.reset();
    ds.select(addr);
    ds.write(0xBE);

    for (i = 0; i < 9; i++)
    {
        data[i] = ds.read();
    }

    // Convert the data to actual temperature
    // because the result is a 16 bit signed integer, it should
    // be stored to an "int16_t" type, which is always 16 bits
    // even when compiled on a 32 bit processor.
    int16_t raw = (data[1] << 8) | data[0];
    if (type_s)
    {
        raw = raw << 3;
        if (data[7] == 0x10)
        {
            raw = (raw & 0xFFF0) + 12 - data[6];
        }
    }
    else
    {
        byte cfg = (data[4] & 0x60);
        // at lower res, the low bits are undefined, so let's zero them
        if (cfg == 0x00)
            raw = raw & ~7; // 9 bit resolution, 93.75 ms
        else if (cfg == 0x20)
            raw = raw & ~3; // 10 bit res, 187.5 ms
        else if (cfg == 0x40)
            raw = raw & ~1; // 11 bit res, 375 ms
                            //// default is 12 bit resolution, 750 ms conversion time
    }
    celsius = (float)raw / 16.0;
    //  fahrenheit = celsius * 1.8 + 32.0;
    Serial.print("Temperature: ");
    Serial.println(celsius);
    //  Serial.print(" Celsius, ");
    //  Serial.print(fahrenheit);
    //  Serial.println(" Fahrenheit");
}