/**************************************************************************/
/*!
This is a demo for the Adafruit MCP9808 breakout
----> http://www.adafruit.com/products/1782
Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!
*/
/**************************************************************************/

#include <Wire.h>
#include "Adafruit_MCP9808.h"

#define tempsensor18address 0x18
#define tempsensor19address 0x19
#define tempsensor1Aaddress 0x1A

// Create the MCP9808 temperature sensor object
Adafruit_MCP9808 tempsensor18 = Adafruit_MCP9808();
Adafruit_MCP9808 tempsensor19 = Adafruit_MCP9808();
Adafruit_MCP9808 tempsensor1A = Adafruit_MCP9808();


void setup() {
  Serial.begin(9600);
  Serial.println("MCP9808 demo");
  Wire.begin();

  // Make sure the sensor is found, you can also pass in a different i2c
  // address with tempsensor.begin(0x19) for example
  if (!tempsensor18.begin(tempsensor18address)) {
    Serial.println("Couldn't find 18 MCP9808!");
    while (1);
  }
  if (!tempsensor19.begin(tempsensor19address)) {
//   Serial.println("Couldn't find 19 MCP9808!");
    while (1);
  }
  if (!tempsensor1A.begin(tempsensor1Aaddress)) {
    Serial.println("Couldn't find 1A MCP9808!");
    while (1);
  }
}

void loop() {
  // Read and print out the temperature
  float c18 = tempsensor18.readTempC();
  Serial.print("Temp18: "); Serial.print(c18); Serial.println("*C\t"); 
  delay(250);

  float c19 = tempsensor19.readTempC();
  Serial.print("Temp19: "); Serial.print(c19); Serial.println("*C\t"); 
  delay(250);

  float c1A = tempsensor1A.readTempC();
  Serial.print("Temp1A: "); Serial.print(c1A); Serial.println("*C\t"); 
  delay(250);
  
}
