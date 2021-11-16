
// Arduino analog input 5 - I2C SCL
// Arduino analog input 4 - I2C SDA
/*
 In this example we will do a basic read of the CO2 value and
checksum verification.
 For more advanced applications please see the I2C Comm guide.
*/
#include <SoftwareSerial.h>
#include <Wire.h>
#include "SFE_HMC6343.h"

#define ADDR_6713 0x15 // default I2C slave address
SFE_HMC6343 compass; // Declare the sensor object

SoftwareSerial OpenLog(10, 11); //declares sd card OpenLog

int data [4];
int CO2ppmValue;
// This is the default address of the CO2 sensor, 7bits shifted left.
void setup() {
 Wire.begin ();
 OpenLog.begin(9600);
 OpenLog.println("Application Note AN161_ardunio_T6713_I2C");

// Give the HMC6343 a half second to wake up
  delay(500); 

  // Initialize the HMC6343 and verify its physical presence
  if (!compass.init())
  {
    Serial.println("Sensor Initialization Failed\n\r"); // Report failure, is the sensor wiring correct?
  }
 
}
//////////////////////////////////////////////////////////////////
// Function : int readCO2()
// Returns : CO2 Value upon success, 0 upon checksum failure
// Assumes : - Wire library has been imported successfully.
// - LED is connected to IO pin 13
// - CO2 sensor address is defined in co2_addr
//////////////////////////////////////////////////////////////////

int readC02()
{
 // start I2C
  Wire.beginTransmission(ADDR_6713);
 Wire.write(0x04); Wire.write(0x13); Wire.write(0x8B);
Wire.write(0x00); Wire.write(0x01);
 // end transmission
 Wire.endTransmission();
 // read report of current gas measurement in ppm
 delay(2000);
 Wire.requestFrom(ADDR_6713, 4); // request 4 bytes from slave device
 data[0] = Wire.read();
 data[1] = Wire.read();
 data[2] = Wire.read();
 data[3] = Wire.read();
 OpenLog.print("Func code: "); OpenLog.print(data[0],HEX);
 OpenLog.print(" byte count: "); OpenLog.println(data[1],HEX);
 OpenLog.print("MSB: 0x"); OpenLog.print(data[2],HEX);
OpenLog.print(" ");
 OpenLog.print("LSB: 0x"); OpenLog.print(data[3],HEX);
OpenLog.print(" ");
 CO2ppmValue = ((data[2] * 0xFF ) + data[3]);
}

void printHeadingData()
{
  OpenLog.println("Heading Data (Raw value, in degrees):");
  OpenLog.println();
  OpenLog.print("Heading: ");
  OpenLog.print(compass.heading); OpenLog.print("  "); // Print raw heading value
  OpenLog.print((float) compass.heading/10.0);OpenLog.write(176);OpenLog.println(); // Print heading in degrees
  OpenLog.print("Pitch: ");
  OpenLog.print(compass.pitch); OpenLog.print("  ");
  OpenLog.print((float) compass.pitch/10.0);OpenLog.write(176);OpenLog.println();
  OpenLog.print("Roll: ");
  OpenLog.print(compass.roll); OpenLog.print("  ");
  OpenLog.print((float) compass.roll/10.0);OpenLog.write(176);OpenLog.println();
  OpenLog.println();
}

void printAccelData()
{
  OpenLog.println("Accelerometer Data (Raw value, in g forces):");
  OpenLog.print("X: ");
  OpenLog.print(compass.accelX); OpenLog.print("  "); // Print raw acceleration measurement on x axis
  OpenLog.print((float) compass.accelX/1024.0);OpenLog.println("g"); // Print x axis acceleration measurement in g forces
  OpenLog.print("Y: ");
  OpenLog.print(compass.accelY); OpenLog.print("  ");
  OpenLog.print((float) compass.accelY/1024.0);OpenLog.println("g");
  OpenLog.print("Z: ");
  OpenLog.print(compass.accelZ); Serial.print("  ");
  OpenLog.print((float) compass.accelZ/1024.0);OpenLog.println("g");
  OpenLog.println();
}
void loop() 
{

// Read, calculate, and print the heading, pitch, and roll from the sensor
  compass.readHeading();
  printHeadingData();
  
  // Read, calculate, and print the acceleration on the x, y, and z axis of the sensor
  compass.readAccel();
  printAccelData();
  
  // Wait for two seconds
  delay(2000); // Minimum delay of 200ms (HMC6343 has 5Hz sensor reads/calculations)
 int co2Value =readC02();
 {
 OpenLog.print("CO2 Value: ");
 OpenLog.println(CO2ppmValue);
 }

 delay(2000);
} 
