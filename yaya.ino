

// Load Libraries for DS1820 and OneWire
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
 
// Variables for temperature readings
float myTemp;
float myHighTemp;
float myLowTemp = 50;
float mycookdo = 52.80;

// DS1820 Data wire is plugged into pin 4 on the Arduino
#define ONE_WIRE_BUS 6
// 建立 LiquidCrystal 的變數 lcd
//                 LCD 接腳:  rs, enable, d4, d5, d6, d7 
//      對應到 Arduino 接腳:  12,     11,  5,  4,  3,  2
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// Setup oneWire instance to communicate with devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
const int relayPin = 7;
int relayState = 0; 


void setup()
{
  lcd.begin(16, 2);
  lcd.print("hello, world!");
  // start serial port
  pinMode(relayPin, OUTPUT); 
   // Start the OneWire library
   sensors.begin();
}

void loop()
{

  // Read the temperature
  readtemp();
  // Write the Results to the serial Monitor
  lcd.setCursor(0, 0);
  lcd.clear();
  // 列印 Arduino 重開之後經過的秒數
  
  lcd.print("S:");
  lcd.print(mycookdo);
  
  lcd.print("  N:");
  lcd.print(myTemp);
  lcd.setCursor(0, 1);
  
  if (myTemp<mycookdo){
    relayState = 0;
    lcd.print("HOT:ON");
  }
  else{
    relayState = 1;
    lcd.print("HOT:OFF");
  }
  lcd.print("  Ti:");
  lcd.print(millis()/1000);
  digitalWrite(relayPin, relayState);
}

void readtemp()
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  sensors.requestTemperatures(); // Send the command to get temperatures
  myTemp = (sensors.getTempCByIndex(0));
}

