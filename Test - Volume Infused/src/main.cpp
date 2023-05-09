#include <Arduino.h>
#include <HX711.h>

#define calibration_factor 1 //This value is obtained using the SparkFun_HX711_Calibration sketch
#define VI_DOUT  4
#define VI_SCK  5

HX711 loadcell;
void readVolumeInfusedLoadcell();

void setup() {
  Serial.begin(9600);
  Serial.println("UDSWB Volume Infused System Testing");
  
  loadcell.begin(VI_DOUT, VI_SCK);
  Serial.println("Loadcell initiated");

  loadcell.set_scale(calibration_factor); 
  //This value is obtained by using the SparkFun_HX711_Calibration sketch
  //scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  Serial.println("Readings:");
}

void loop() {
  readVolumeInfusedLoadcell();
  delay(20);
}

void readVolumeInfusedLoadcell() {
  Serial.print(millis());
  Serial.print(",");
  Serial.println(loadcell.read());
}