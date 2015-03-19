/**************************************************************************/
/*!
Author: Kirk Ewing
This is a demo for the Adafruit MCP9808 breakout

*/
/**************************************************************************/

#include <Wire.h>
#include "Adafruit_MCP9808.h"
#include "Adafruit_RGBLCDShield.h"


#define coldTempSensorAddress 0x18
#define hotTempSensorAddress 0x19
#define beerTempSensorAddress 0x1A

// These #defines make it easy to set the backlight color
#define RED 0x1
#define GREEN 0x2
#define YELLOW 0x3
#define BLUE 0x4
#define VIOLET 0x5
#define TEAL 0x6
#define WHITE 0x7

// Create the variable to represent the LCD Shield
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();



// Create the MCP9808 temperature sensor object
Adafruit_MCP9808 coldTempSensor = Adafruit_MCP9808();
Adafruit_MCP9808 hotTempSensor = Adafruit_MCP9808();
Adafruit_MCP9808 beerTempSensor = Adafruit_MCP9808();

boolean coldError = false;
boolean hotError = false;
boolean beerError = false;


void setup() {
  Serial.begin(9600);
  Serial.println("Temp Monitoring Program");
  Wire.begin();

  // Make sure the sensor is found, you can also pass in a different i2c
  // address with tempsensor.begin(0x19) for example
  coldError = !coldTempSensor.begin(coldTempSensorAddress);
  hotError = !hotTempSensor.begin(hotTempSensorAddress);
  beerError = !beerTempSensor.begin(beerTempSensorAddress);

  //Write to Serial if any sensor isn't found
  if (coldError) Serial.println("Couldn't find coldSensor!");
  if (hotError) Serial.println("Couldn't find hotSensor!");
  if (beerError) Serial.println("Couldn't find beerSensor!");

  // Setup the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Setup the LCD backlight to White
  lcd.setBacklight(WHITE);

}

void loop() {

  float coldTemp = 0;
  float hotTemp = 0;
  float beerTemp = 0;
  /*
  // Read and print out the temperature
  float coldTemp = coldTempSensor.readTempC();
  Serial.print("Cold: "); Serial.print(coldTemp); Serial.print("*C\t     ");
  delay(250);

  float hotTemp = hotTempSensor.readTempC();
  Serial.print("Hot: "); Serial.print(hotTemp); Serial.print("*C\t     ");
  delay(250);

  float beerTemp = beerTempSensor.readTempC();
  Serial.print("Beer: "); Serial.print(beerTemp); Serial.print("*C\t     ");
  delay(250);
*/
  // Clear the LCD screen from previous content. Set cursor to first Char on Line 1
  // setCursor first var is Column, Second is Line
  lcd.clear();
  lcd.setCursor(0, 0);


  // If no error, Read Temperatures, else restart sensor
  if (!coldError)
  {
    coldTemp = coldTempSensor.readTempC(); // Read Cold Temp

    Serial.print("Cold Temp: "); // Write Cold Temp to console
    Serial.print(coldTemp);
    Serial.print("*C ");

        lcd.print("C:"); // Write Cold Temp to the LCD
        lcd.print(coldTemp);
  } else
  {
    Serial.println("Couldn't find cold MCP9808!"); // Write error to console
    //    lcd.print("C Err "); // Write error to LCD
    coldError = !coldTempSensor.begin(coldTempSensorAddress); // Restart Cold Sensor
  }
  
  if (!hotError)
  {
    hotTemp = hotTempSensor.readTempC(); // Read Hot Temp

    Serial.print("Hot Temp: "); // Write Hot Temp to console
    Serial.print(hotTemp);
    Serial.print("*C ");

    lcd.print(" H:"); // Write Hot Temp to the LCD
    lcd.print(hotTemp);
  } else
  {
    Serial.println("Couldn't find hot MCP9808!"); // Write error to console
    lcd.print("H Err "); // Write error to LCD
    hotError = !hotTempSensor.begin(hotTempSensorAddress); // Restart Hot Sensor
  }
    // Set Cursor to first Char on Line 2
  lcd.setCursor(0, 1);

  if (!beerError)
  {
    beerTemp = beerTempSensor.readTempC(); // Read Beer Temp

    Serial.print("Beer Temp: "); // Write Beer Temp to console
    Serial.print(beerTemp);
    Serial.print("*C\t");

    lcd.print("B:"); // Write Beer Temp to the LCD
    lcd.print(beerTemp);
  } else
  {
    Serial.println("Couldn't find beer MCP9808!"); // Write error to console
    lcd.print("B Err "); // Write error to LCD
    beerError = !beerTempSensor.begin(beerTempSensorAddress); // Restart Beer Sensor
  }
    
  // Print minutes since reset
  Serial.print("Mins: "); Serial.println(millis() / 60000);
  lcd.print (" Mins:"); lcd.print(millis()/60000);
  delay(5000);



}
