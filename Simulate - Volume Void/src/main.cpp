#include <Arduino.h>

float time;
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
  vv = 0.0;
  q = 0.0;
}

void updateValues(){
  time = millis()/1000;
  vv = cos((time*10)+15) * getRandomValue(35.0);
  q = cos((time*10)+30) * getRandomValue(35.0);
}

void printValues(){
  Serial.print(time);
  Serial.print(",");
  Serial.print(vv);
  Serial.print(",");
  Serial.println(q);
}