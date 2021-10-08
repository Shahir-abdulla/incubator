#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void init_display()
{

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;
    }

    // Clear the buffer.
    display.clearDisplay();

    display.clearDisplay();
    display.setTextColor(WHITE);
    //display.startscrollright(0x00, 0x0F); // You can uncomment this line to scroll your text on oled
    //  display.setTextSize(2);
    //  display.setCursor(0,5);
    //  display.print("  Incubator "); //This will Display Clock on OLED for 3 seconds
    //  display.display();
    //  delay(3000);
}

void show_elements()
{
    display.clearDisplay();

    //-----------to display temeperature-------------
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Temperature: ");

    display.setTextSize(3);
    display.setCursor(0, 12);
    display.println(celsius);

    display.setTextSize(1);
    display.setCursor(102, 12);
    display.write(167);

    display.setTextSize(3);
    display.setCursor(110, 12);
    display.println("C");

    //-------------to display incubation period-------
    display.setTextSize(1);
    display.setCursor(0, 40);
    display.println("Incubation Period:");

    display.setTextSize(1);
    display.setCursor(115, 40);
    display.println(12);

    //------------to display date ------
    display.setTextSize(1);
    display.setCursor(0, 55);
    display.println("Date:");

    display.setTextSize(1);
    display.setCursor(50, 55);
    display.println(now.day(), DEC);

    display.setTextSize(1);
    display.setCursor(65, 55);
    display.println("/");

    display.setTextSize(1);
    display.setCursor(75, 55);
    display.println(now.month(), DEC);

    display.setTextSize(1);
    display.setCursor(90, 55);
    display.println("/");

    display.setTextSize(1);
    display.setCursor(100, 55);
    display.println(now.year(), DEC);

    display.display();
}