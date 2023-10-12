#include <Arduino.h>
#include "controlmanager.h"

ControlManager manager;

float millis_start;
int pump_value;
float time;
float pblad;
float pabd;
float pdet;
float vi;
float vv;
float q;

void initValues(){
  millis_start = millis();
  pump_value=0;
  time = 0.0;
  pblad = 0.0;
  pabd = 0.0;
  pdet = 0.0;
  vi = 0.0;
  vv = 0.0;
  q = 0.0;
}

void updateValues(){
  time = millis() - millis_start;
  pblad = 31+(sin(time*10));
  pabd = 30+(sin((time*10)+15));
  pdet = 0;
  vi = vi+0.004; //= 10+(cos(time*10));
  vv = vv+0.003;// = 10+(cos((time*10)+15));
  q = (int) (((float) pump_value/255.0) * 100);
}

void sendValues(){
  Serial.print("Time");
  Serial.print(",");
  Serial.print(time);
  Serial.print(";PBLAD,");
  Serial.print(pblad);
  Serial.print(";PABD,");
  Serial.print(pabd);
  Serial.print(";PDET,");
  Serial.print(pdet);
  Serial.print(";VI,");
  Serial.print(vi);
  Serial.print(";VV,");
  Serial.print(vv);
  Serial.print(";Q,");
  Serial.println(q);
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
