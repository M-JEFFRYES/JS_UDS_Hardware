#include <Arduino.h>

float time;
float pblad;
float pabd;
float pdet;
float vi;
float vv;
float q;
float getRandomValue(float);
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

float getRandomValue(float range){
  return range * (rand() / (range + 1.0));
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
  pblad = sin(time*10) * getRandomValue(35.0);
  pabd = sin((time*10)+15) * getRandomValue(35.0);
  pdet = sin((time*10)+30) * getRandomValue(35.0);
  vi = cos(time*10) * getRandomValue(35.0);
  vv = cos((time*10)+15) * getRandomValue(35.0);
  q = cos((time*10)+30) * getRandomValue(35.0);
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