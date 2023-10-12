#include <Arduino.h>
#include <HX711.h>
#include "controlmanager.h"

ControlManager manager;

#define calibration_factor 1 //This value is obtained using the SparkFun_HX711_Calibration sketch
#define VV_DOUT  2
#define VV_SCK  3

float millis_start;
float time;
float vv;

HX711 loadcell;

void initValues(){
  millis_start = millis();
  time = 0.0;
  vv = 0.0;
}

void updateValues() {
  time = millis() - millis_start;
  vv = loadcell.read();
}

void sendValues() {
  Serial.print("Time,");
  Serial.print(millis());
  Serial.print(";VV,");
  Serial.println(vv);
}

void setup() {
  Serial.begin(manager.getBaudRate());

  loadcell.begin(VV_DOUT, VV_SCK);
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