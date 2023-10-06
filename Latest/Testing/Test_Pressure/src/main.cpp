#include <Arduino.h>
#include "MS5840_I2C.h"
#include <Wire.h>

const int BAUD_RATE = 9600;

const int START_TRANSMISSION_CODE = 333;
const int END_TRANSMISSION_CODE = 444;
const unsigned int MAX_MESSAGE_LENGTH = 5;

float millis_start;
bool send_data;

float time;
float psens1;
float psens2;

const uint8_t ind1 = 0;
const uint8_t ind2 = 1;
const int sensor_delay = 50;
MS5840 sensor1(ADDRESS_HIGH);
MS5840 sensor2(ADDRESS_HIGH);

void initValues();
void updateValues();
void printValues();
void TCA9548A(uint8_t bus);
double get_sensor_pressure(int MUX_index, MS5840 sensor);

void setup() {
  Serial.begin(BAUD_RATE);
  initValues();

  TCA9548A(ind1);
  sensor1.reset();
  sensor1.begin();

  TCA9548A(ind2);
  sensor2.reset();
  sensor2.begin();
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
  time = 0.0;
  psens1 = 0.0;
  psens2 = 0.0;
}

void updateValues(){
  time = millis()-millis_start;
  psens1 = get_sensor_pressure(ind1, sensor1);
  delay(sensor_delay);

  psens2 = get_sensor_pressure(ind2, sensor2);
  delay(sensor_delay);
}

void printValues(){
  Serial.print("Time,");
  Serial.print(time);
  Serial.print(";PSENS1,");
  Serial.print(psens1);
  Serial.print(";PSENS1,");
  Serial.println(psens2);
}

void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  //Serial.print(bus);
}

double get_sensor_pressure(int MUX_index, MS5840 sensor){
  TCA9548A(MUX_index); // Set multiplexer channel
  double pressure_pa = sensor.getPressure(ADC_256); // get pressure in pascal
  double pressure_h2o = pressure_pa * 0.010197162129779282; // convert to COM
  return pressure_h2o;
}

