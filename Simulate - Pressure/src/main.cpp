#include <Arduino.h>

float time;
float pblad;
float pabd;
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
}

void updateValues(){
  time = millis()/1000;
  pblad = sin(time*10) * getRandomValue(35.0);
  pabd = sin((time*10)+15) * getRandomValue(35.0);
}

void printValues(){
  Serial.print(time);
  Serial.print(",");
  Serial.print(pblad);
  Serial.print(",");
  Serial.println(pabd);
}