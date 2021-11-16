#include <SoftwareSerial.h>
#include <Wire.h>
#include "SFE_HMC6343.h"

SFE_HMC6343 compass; // Declare the sensor object

const int gasPin1 = A0; //GAS sensor output pin to Arduino analog A0 pin
//const int gasPin2 = A1;
//const int gasPin3 = A2;
SoftwareSerial OpenLog(10, 11);

void setup()
{
 OpenLog.begin(9600); //Open software serial port at 9600bps
 Serial.begin(9600);

 // Give the HMC6343 a half second to wake up
  delay(500); 
  
  // Start I2C
  Wire.begin();

  // Initialize the HMC6343 and verify its physical presence
  if (!compass.init())
  {
    Serial.println("Sensor Initialization Failed\n\r"); // Report failure, is the sensor wiring correct?
  }
 
  
 // OpenLog.print("MQ-135");
 // OpenLog.print("\t");
 // OpenLog.print("\t");
 // OpenLog.print("MQ-4");
 // OpenLog.print("\t");
 // OpenLog.print("\t");
 // OpenLog.print("Elevation");
 // OpenLog.print("\t");
 // OpenLog.print("\t");
 // OpenLog.println();
 // OpenLog.print("-----------------------------------------");
 // OpenLog.println();
  
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
}

// Print both the raw values of the compass heading, pitch, and roll
// as well as calculate and print the compass values in degrees
// Sample Output:
// Heading Data (Raw value, in degrees):
// Heading: 3249  324.90°
// Pitch:   28    2.80°
// Roll:    24    2.40°
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

// Print both the raw values of the compass acceleration measured on each axis
// as well as calculate and print the accelerations in g forces
// Sample Output:
// Accelerometer Data (Raw value, in g forces):
// X: -52    -0.05g
// Y: -44    -0.04g
// Z: -1047  -1.02g
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



 OpenLog.println();
 OpenLog.print(analogRead(gasPin1));
// OpenLog.print("\t");
 //OpenLog.print("\t");
 //OpenLog.print(analogRead(gasPin2));
 //OpenLog.print("\t");
 //OpenLog.print("\t");
 //OpenLog.print(analogRead(gasPin3));
 //OpenLog.print("\t");
 //OpenLog.print("\t");
 //OpenLog.println();
 delay(5000); // Print value every 1 sec.
}
