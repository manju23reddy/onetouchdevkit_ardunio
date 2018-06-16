#include "device_motor.h"
#include "sensor_state.h"
#include "hw_config.h"
#include <Wire.h>
#include "user_interface.h"
#include <WiFiUdp.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>

DeviceMotor::DeviceMotor(){
  mMotor_Control = ON;
  mMotor_Mode = MOTOR_SHORT_PULSE;  
}

DeviceMotor::~DeviceMotor(){
}
void DeviceMotor::set_motor_control(SENSOR_STATE state){
  mMotor_Control = state;
}
void  DeviceMotor::set_motor_mode(MOTOR_MODE motor_mode){
  mMotor_Mode = motor_mode;
}

SENSOR_STATE DeviceMotor::get_motor_control(){
  return mMotor_Control;
}
MOTOR_MODE DeviceMotor::get_motor_mode(){
  return mMotor_Mode;
}

