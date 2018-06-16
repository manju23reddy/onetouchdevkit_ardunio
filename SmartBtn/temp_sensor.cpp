#include "temp_sensor.h"
#include "sensor_state.h"
#include "hw_config.h"
#include <Wire.h>
#include "user_interface.h"
#include <WiFiUdp.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>

TempSensor::TempSensor(){
	mTemp_Control = OFF;
  mTemp_Threshold_Low = 0.0;
  mTemp_Threshold_High = 0.0;
}
TempSensor::~TempSensor(){
}
void TempSensor::set_temperature_sensor_control(SENSOR_STATE state){
	mTemp_Control = state;	
}

SENSOR_STATE TempSensor::get_temperature_sensor_control(){
	return mTemp_Control;
}

float TempSensor::get_current_temperature(){
	Wire.beginTransmission(TEMP_SENSOR);
	Wire.write(1);
	Wire.write(0);
	Wire.endTransmission();

	Wire.beginTransmission(TEMP_SENSOR);
	Wire.write(0);  
	Wire.endTransmission();
	Wire.requestFrom(TEMP_SENSOR, 2);
	word regdata = (Wire.read() << 8) | Wire.read();
	return (((float)(int)regdata / 32) / 8);
		
}

void TempSensor::set_temperature_threshold_low(float thresholdLow){
  mTemp_Threshold_Low = thresholdLow;
}
void TempSensor::set_temperature_threshold_high(float thresholdHigh){
  mTemp_Threshold_High = thresholdHigh;
}

float TempSensor::get_temperature_threshold_low(){
  return mTemp_Threshold_Low;
}
float TempSensor::get_temperature_threshold_high(){
  return mTemp_Threshold_High;
}



