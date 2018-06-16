#include "device_buzzer.h"
#include "sensor_state.h"
#include "hw_config.h"
#include <Wire.h>
#include "user_interface.h"
#include <WiFiUdp.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>

DeviceBuzzer::DeviceBuzzer(){
  mBuzzer_Control = OFF;
  mBuzzer_Mode = BUZZER_SHORT_PULSE;  
}

DeviceBuzzer::~DeviceBuzzer(){
}
void DeviceBuzzer::set_buzzer_control(SENSOR_STATE state){
  mBuzzer_Control = state;
}
void  DeviceBuzzer::set_buzzer_mode(BUZZER_MODE buzzer_mode){
  mBuzzer_Mode = buzzer_mode;
}

SENSOR_STATE DeviceBuzzer::get_buzzer_control(){
  return mBuzzer_Control;
}
BUZZER_MODE DeviceBuzzer::get_buzzer_mode(){
  return mBuzzer_Mode;
}
