#include <Arduino.h>

float time;
float vi;
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
  delay(50);
}

void initValues(){
  time = 0.0;
  vi = 0.0;
}

void updateValues(){
  time = millis()/1000;
  vi = cos((time*10))*10;
}

void printValues(){
  Serial.print(time);
  Serial.print(",");
  Serial.println(vi);
}