#include <Arduino.h>
#include "controlmanager.h"

ControlManager manager;

float millis_start;
int pump_value;
float time;
float vi;

void initValues(){
  millis_start = millis();
  time = 0.0;
  vi = 0.0;
}

void updateValues(){
  time = (millis() - millis_start) / 1000;
  vi = cos((time*10))*10;
}

void sendValues(){
  Serial.print("Time,");
  Serial.print(time);
  Serial.print(";VI,");
  Serial.println(vi);
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


