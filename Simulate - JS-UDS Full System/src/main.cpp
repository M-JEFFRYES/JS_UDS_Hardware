#include <Arduino.h>

float time;
float pblad;
float pabd;
float pdet;
float vi;
float vv;
float q;
void initValues();
void updateValues();
void printValues();


void setup() {
  Serial.begin(9600);
  initValues();
}

void loop() {
  updateValues();
  printValues();
  delay(2);
}

void initValues(){
  time = 0.0;
  pblad = 0.0;
  pabd = 0.0;
  pdet = 0.0;
  vi = 0.0;
  vv = 0.0;
  q = 0.0;
}

void updateValues(){
  time = millis()/1000;
  pblad = sin((time*10))*40;
  pabd = sin((time*10)+15)*25;
  pdet = sin((time*10)+30)*20;
  vi = cos((time*10))*10;
  vv = cos((time*10)+15)*42;
  q = cos((time*10)+30)*46;
}

void printValues(){
  Serial.print(time);
  Serial.print(",");
  Serial.print(pblad);
  Serial.print(",");
  Serial.print(pabd);
  Serial.print(",");
  Serial.print(pdet);
  Serial.print(",");
  Serial.print(vi);
  Serial.print(",");
  Serial.print(vv);
  Serial.print(",");
  Serial.println(q);
}