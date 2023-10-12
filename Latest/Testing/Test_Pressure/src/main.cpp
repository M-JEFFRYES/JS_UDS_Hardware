#include <Arduino.h>
#include "MS5840_I2C.h"
#include <Wire.h>
#include "controlmanager.h"

ControlManager manager;

float millis_start;
float time;
float psens1;
float psens2;

const uint8_t ind1 = 0;
const uint8_t ind2 = 1;
const int sensor_delay = 50;
MS5840 sensor1(ADDRESS_HIGH);
MS5840 sensor2(ADDRESS_HIGH);

// SENSOR MEASUREMENT
void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  //Serial.print(bus);
}

double get_sensor_pressure(int MUX_index, MS5840 sensor){
  TCA9548A(MUX_index); // Set multiplexer channel
  double pressure_pa = sensor.getPressure(ADC_256); // get pressure in pascal
  double pressure_h2o = pressure_pa * 0.010197162129779282; // convert to COM
  return pressure_h2o;
}

// DATA MANAGEMENT
void initValues(){
  millis_start = millis();
  time = 0.0;
  psens1 = 0.0;
  psens2 = 0.0;
}

void updateValues(){
  time = millis()-millis_start;
  psens1 = get_sensor_pressure(ind1, sensor1);
  delay(sensor_delay);

  psens2 = get_sensor_pressure(ind2, sensor2);
  delay(sensor_delay);
}

void sendValues(){
  Serial.print("Time,");
  Serial.print(time);
  Serial.print(";PSENS1,");
  Serial.print(psens1);
  Serial.print(";PSENS1,");
  Serial.println(psens2);
}

void setup() {
  Serial.begin(manager.getBaudRate());

  TCA9548A(ind1);
  sensor1.reset();
  sensor1.begin();

  TCA9548A(ind2);
  sensor2.reset();
  sensor2.begin();

  manager.loadInitDataFunction(initValues);
  manager.loadCollectDataFunction(updateValues);
  manager.loadSendDataFunction(sendValues);
  manager.runInitDataFunction();
}

void loop() {
  while (Serial.available()>0){
    manager.checkSerialMessagesIn();
  }
  manager.sendDataTransmission();
  delay(2);
}