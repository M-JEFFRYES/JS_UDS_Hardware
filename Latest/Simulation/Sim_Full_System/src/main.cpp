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
        vv = 0.0;
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
  millis_start = 0;
  send_data = false;
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

void printValues(){
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
