#include <Arduino.h>

const int BAUD_RATE = 9600;

const int START_TRANSMISSION_CODE = 333;
const int END_TRANSMISSION_CODE = 444;
const int PUMP_PWM_MAX = 256;
const unsigned int MAX_MESSAGE_LENGTH = 5;

float millis_start;
bool send_data;
int pump_value;

float time;
float vi;

void initValues();
void updateValues();
void printValues();


void setup() {
  Serial.begin(BAUD_RATE);
  initValues();
}

void loop() {
  while (Serial.available()>0){
    static char message[MAX_MESSAGE_LENGTH];
    static unsigned int message_pos=0;

    char inByte = Serial.read();

    if (inByte != '\n'){
      message[message_pos] = inByte;
      message_pos++;

    } else {
      message[message_pos] = '\0';
      int number = atoi(message);

      if (number == START_TRANSMISSION_CODE){
        millis_start = millis();
        vi = 0.0;
        send_data = true;
      } else if (number == END_TRANSMISSION_CODE) {
        send_data = false;
      } else if (number < PUMP_PWM_MAX ) {
        pump_value = number;
      }
      message_pos = 0;
    }
  }

  if (send_data){
    updateValues();
    printValues();
  }
  delay(2);
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
  Serial.print("Time,");
  Serial.print(time);
  Serial.print(";VI,");
  Serial.println(vi);
}