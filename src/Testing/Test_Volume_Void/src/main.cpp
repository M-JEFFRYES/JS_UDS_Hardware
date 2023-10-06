#include <Arduino.h>
#include <HX711.h>

#define calibration_factor 1 //This value is obtained using the SparkFun_HX711_Calibration sketch
#define VV_DOUT  2
#define VV_SCK  3

const int BAUD_RATE = 9600;

const int START_TRANSMISSION_CODE = 333;
const int END_TRANSMISSION_CODE = 444;
const unsigned int MAX_MESSAGE_LENGTH = 5;

float millis_start;
bool send_data;

float time;
float vv;

HX711 loadcell;

void initValues();
void updateValues();
void printValues();

void setup() {
  Serial.begin(BAUD_RATE);
  initValues();

  loadcell.begin(VV_DOUT, VV_SCK);
  loadcell.set_scale(calibration_factor); 
  //This value is obtained by using the SparkFun_HX711_Calibration sketch
  //scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
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
        vv = loadcell.read();
        send_data = true;
      } else if (number == END_TRANSMISSION_CODE) {
        send_data = false;
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
  time = 0.0;
  vv = 0.0;
}

void updateValues() {
  time = millis() - millis_start;
  vv = loadcell.read();
}

void printValues() {
  Serial.print("Time,");
  Serial.print(millis());
  Serial.print(";VV,");
  Serial.println(vv);
}

