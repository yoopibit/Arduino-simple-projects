/**
 * Sensor which print output from light 
 * sensor, water senor, temperature and humidity (pin 7).
 * Lcd display connected by A4 and A5 pin (by default), 
 * where A4 => SDA, A5 => SCL
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <my_string.h>
#include <dht.h>

#define DHT11_PIN   (7)
#define lightPin    (A0)
#define waterLevel  (A1)
#define tempPin    (A3)
char str[16];
dht DHT;
LiquidCrystal_I2C lcd(0x3F, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd
  lcd.backlight();}

void loop()
{
     
  DHT.read11(DHT11_PIN);
  write_lght_tmp_hmd_watr(analogRead(lightPin), getTemp(), DHT.humidity, analogRead(waterLevel));
}

void write_lght_tmp_hmd_watr(int light, int temp, int hmd, int water)
{
  lcd.clear();
  lcd.print("Light = ");
  lcd.print(long_to_str(light, str, sizeof(str)));
  lcd.setCursor(0,1);
  lcd.print("Temp = ");
  lcd.print(double_to_str(temp, str, sizeof(str)));
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Humidity = ");
  lcd.print(long_to_str(hmd, str, sizeof(str)));
  lcd.setCursor(0,1);
  lcd.print("Water = ");
  lcd.print(long_to_str(water, str, sizeof(str)));
  delay(1500);
}

inline double getTemp()
{
  double temp = (double)analogRead(tempPin); 
  return temp * 5.0 * 100.0 / 1024.0;
}


