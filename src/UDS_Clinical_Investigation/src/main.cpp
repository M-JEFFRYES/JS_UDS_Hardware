#include <Arduino.h>
#include <HX711.h>
#include "MS5840_I2C.h"
#include <Wire.h>

#define vi_calibration_factor 1 //This value is obtained using the SparkFun_HX711_Calibration sketch
#define vv_calibration_factor 1 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define VV_DOUT  2
#define VV_SCK  3

#define VI_DOUT  4
#define VI_SCK  5
#define PUMP_PIN 9

const double PA_TO_CMH2O = 0.010197162129779282;
const uint8_t ind1 = 0;
const uint8_t ind2 = 1;
const int PSENS_DELAY = 50;
MS5840 sensor1(ADDRESS_HIGH);
MS5840 sensor2(ADDRESS_HIGH);

const int BAUD_RATE = 9600;

const int START_TRANSMISSION_CODE = 333;
const int END_TRANSMISSION_CODE = 444;
const int PUMP_PWM_MAX = 256;
const unsigned int MAX_MESSAGE_LENGTH = 5;

float millis_start;
bool send_data;
int pump_value;
float time;
double pblad;
double pabd;
float vv;
float vi;

HX711 loadcell_vi;
HX711 loadcell_vv;

void initValues();
void updateValues();
void printValues();
void TCA9548A(uint8_t bus);
double get_sensor_pressure(int MUX_index, MS5840 sensor);

void setup() {
  Serial.begin(BAUD_RATE);
  initValues();

  loadcell_vi.begin(VI_DOUT, VI_SCK);
  loadcell_vi.set_scale(vi_calibration_factor); 

  loadcell_vv.begin(VV_DOUT, VV_SCK);
  loadcell_vv.set_scale(vv_calibration_factor); 

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
      } else if (number < PUMP_PWM_MAX ) {
        pump_value = number;
        analogWrite(PUMP_PIN, pump_value);
      }
      message_pos = 0;
    }
  }

  if (send_data){
    updateValues();
    printValues();
  }
}

void initValues(){
  millis_start = 0;
  pump_value = 0;
  send_data = false;
  time = 0.0;
  pblad = 0.0;
  pabd = 0.0;
  vi = 0.0;
  vv = 0.0;
}

void updateValues() {
  time = millis() - millis_start;
  vi = loadcell_vi.read();
  vv = loadcell_vv.read();
  pblad = get_sensor_pressure(ind1, sensor1);
  delay(PSENS_DELAY);
  pabd = get_sensor_pressure(ind2, sensor2);
  delay(PSENS_DELAY);

}

void printValues() {
  Serial.print("Time,");
  Serial.print(time);
  Serial.print(";PBLAD,");
  Serial.print(pblad);
  Serial.print(";PABD,");
  Serial.print(pabd);
  Serial.print(";VV,");
  Serial.print(vv);
  Serial.print(";VI,");
  Serial.println(vi);
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
  double pressure_h2o = pressure_pa * PA_TO_CMH2O; // convert to COM
  return pressure_h2o;
}