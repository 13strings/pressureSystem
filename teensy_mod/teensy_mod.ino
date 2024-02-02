#include <Wire.h>
#include "MS5837.h"

MS5837 sensor;
MS5837 sensor1;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  
  Serial.println("Starting");
  
  Wire.begin();
  Wire.setSDA(18);
  Wire.setSCL(19);
  Wire1.begin();
  Wire1.setSDA(17);
  Wire1.setSCL(16);
 
  sensor.init(Wire);
  sensor.setModel(MS5837::MS5837_02BA);
  sensor.setFluidDensity(1.2); // kg/m^3 (freshwater, 1029 for seawater)
  
  sensor1.init(Wire1);
  sensor1.setModel(MS5837::MS5837_02BA);
  sensor1.setFluidDensity(1.2); // kg/m^3 (freshwater, 1029 for seawater)
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor.read();
  //Serial.print("Pressure 0: "); 
  Serial.print(sensor.pressure()); 
  //Serial.println(" mbar");
  Serial.print(",");

  sensor1.read();
  //Serial.print("Pressure 1: "); 
  Serial.print(sensor1.pressure()); 
  //Serial.println(" mbar");
  Serial.println();
  //Serial.print("Temperature: "); 
  //Serial.print(sensor.temperature()); 
  //Serial.println(" deg C");

  delay(1);
}
