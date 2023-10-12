#include <Arduino.h>
#include "controlmanager.h"

ControlManager manager;

float millis_start;
float time;
float pblad;
float pabd;

void initValues(){
  millis_start = millis();
  time = 0.0;
  pblad = 0.0;
  pabd = 0.0;
}

void updateValues(){
  time = millis() - millis_start;
  pblad = 31+(sin(time*10));
  pabd = 30+(sin((time*10)+15));
}

void sendValues(){
  Serial.print("Time,");
  Serial.print(time);
  Serial.print(";PBLAD,");
  Serial.print(pblad);
  Serial.print(";PABD,");
  Serial.println(pabd);
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