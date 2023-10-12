#include <Arduino.h>
#include "controlmanager.h"

ControlManager manager;

float millis_start;
float time;
float vv;

void initValues(){
  millis_start = millis();
  time = 0.0;
  vv = 0.0;
}

void updateValues(){
  time = (millis() - millis_start) / 1000;
  vv = cos((time*10))*10;
}

void sendValues(){
  Serial.print("Time,");
  Serial.print(time);
  Serial.print(";VV,");
  Serial.println(vv);
}

void setup() {
  Serial.begin(manager.getBaudRate());
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