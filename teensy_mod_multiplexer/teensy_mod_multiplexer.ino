#include <Wire.h>
#include "MS5837.h"
#include "TCA9548.h"

#define TCAADDR 0x70

// for each device make a difference sensor instance 
MS5837 sensor;
MS5837 sensor1;

// for swithcing between the TCA9548A channels
void tcaselect(uint8_t channel) {
  if (channel > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << channel);
  Wire.endTransmission();  
}

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  Serial.println("Starting");
  
  // only working with one mux for now, this code will copy paste to make more!
  Wire.begin();
  Wire.setSDA(18);
  Wire.setSCL(19);

  // Wire1.begin();
  // Wire1.setSDA(17);
  // Wire1.setSCL(16);

  tcaselect(0);
  sensor.init(); 
  sensor.setModel(MS5837::MS5837_02BA);
  sensor.setFluidDensity(1.2);

  tcaselect(7);
  sensor1.init();
  sensor1.setModel(MS5837::MS5837_02BA);
  sensor1.setFluidDensity(1.2);

  // copy this for new sensors and change the tca select
  // tcaselect(1)
  // sensor1.init();
  // sensor1.setModel(MS5837::MS5837_02BA);
  // sensor1.setFluidDensity(1.2);

}

void loop() {
  float pres1, pres2, temp1, temp2;

  tcaselect(0);
  sensor.read();
  pres1 = sensor.pressure();
  temp1 = sensor.temperature();

  tcaselect(7);
  sensor1.read();
  pres2 = sensor1.pressure();
  temp2 = sensor1.pressure();

  Serial.print(pres1);
  Serial.print(",");
  Serial.print(pres2);
  Serial.println();

  delay(10);
  
  // put your main code here, to run repeatedly:
  // sensor.read();
  // //Serial.print("Pressure 0: "); 
  // Serial.print(sensor.pressure()); 
  // //Serial.println(" mbar");
  // Serial.print(",");

  // sensor1.read();
  // //Serial.print("Pressure 1: "); 
  // Serial.print(sensor1.pressure()); 
  // //Serial.println(" mbar");
  // Serial.println();
  //Serial.print("Temperature: "); 
  //Serial.print(sensor.temperature()); 
  //Serial.println(" deg C");
}
