#include "device_led.h"
#include "sensor_state.h"
#include "hw_config.h"
#include <Wire.h>
#include "user_interface.h"
#include <WiFiUdp.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>

DeviceLED::DeviceLED(){
	mLED_Control = OFF;
	mLED_Mode = BLINKING;
  pinMode(LED_PIN, OUTPUT);
}

void DeviceLED::set_device_led_control(SENSOR_STATE ledState){
	mLED_Control = ledState;
  switch(mLED_Control){
    case ON:
      digitalWrite(LED_PIN, HIGH);
    break;
    case OFF:
      digitalWrite(LED_PIN, LOW);
    break;
    default:
    break;
  }
}

void DeviceLED::set_device_mode(LED_MODE ledMode){
	mLED_Mode = ledMode;
}

LED_MODE DeviceLED::get_device_mode(){
	return mLED_Mode;
}
SENSOR_STATE DeviceLED::get_device_control(){
	return mLED_Control;
}

DeviceLED::~DeviceLED(){
}
