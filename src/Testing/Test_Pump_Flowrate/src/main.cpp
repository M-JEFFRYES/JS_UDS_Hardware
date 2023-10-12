#include <Arduino.h>
#include <HX711.h>
#include "controlmanager.h"

ControlManager manager;

#define calibration_factor 1 //This value is obtained using the SparkFun_HX711_Calibration sketch
#define VI_DOUT  4
#define VI_SCK  5
#define PUMP_PIN 9
const int PUMP_PWM_MAX = 256;

float millis_start;
int pump_value;
float time;
float vi;

HX711 loadcell;


void initValues(){
  millis_start = millis();
  time = 0.0;
  vi = 0.0;
  pump_value = 0;
}

void updateValues() {
  time = millis() - millis_start;
  vi = loadcell.read();
  analogWrite(PUMP_PIN, pump_value);
  // add change value function
}

void sendValues() {
  Serial.print("Time,");
  Serial.print(millis());
  Serial.print(";VI,");
  Serial.println(vi);
}

void setup() {
  Serial.begin(manager.getBaudRate());

  loadcell.begin(VI_DOUT, VI_SCK);
  loadcell.set_scale(calibration_factor); 

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