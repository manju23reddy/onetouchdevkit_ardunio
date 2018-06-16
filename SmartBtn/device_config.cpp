#include "device_config.h"
#include "sensor_state.h"
#include "device_led.h"
#include <string.h>
#include <stdlib.h>
#include <Wire.h>
#include <ESP8266WiFi.h>



OneTouchDevice::OneTouchDevice(const char* key){
  Serial.println("OneTouchDevice ctr start");
	mDevice_Key = (char*)malloc(sizeof(char)+strlen(key));
	strcpy(mDevice_Key, key);
	initSensors();
  Serial.println("OneTouchDevice ctr end");
}

void OneTouchDevice::initSensors(){
	mDevice_LED = new DeviceLED();
  mDevice_Motor = new DeviceMotor();
  mDevice_Buzzer = new DeviceBuzzer();
  mTempSensor = new TempSensor();
}

OneTouchDevice::~OneTouchDevice(){
  	if (NULL != mDevice_Key){
  		free(mDevice_Key);
  		mDevice_Key = NULL;
  	}
  	if (NULL != mDevice_LED){
  		free(mDevice_LED);
  		mDevice_LED = NULL;
  	}
  
   if (NULL != mDevice_Motor){
      free(mDevice_Motor);
      mDevice_Motor = NULL;
   }
  
   if (NULL != mDevice_Buzzer){
      free(mDevice_Buzzer);
      mDevice_Buzzer = NULL;
   }
  
   if (NULL != mTempSensor){
      free(mTempSensor);
      mTempSensor = NULL;
   }
 }

char* OneTouchDevice::get_device_key(){
	return mDevice_Key;
}

DeviceLED* OneTouchDevice::get_device_led(){
	return mDevice_LED;
}

DeviceMotor* OneTouchDevice::get_device_motor(){
  return mDevice_Motor;
}

DeviceBuzzer* OneTouchDevice::get_device_buzzer(){
  return mDevice_Buzzer;
}

TempSensor* OneTouchDevice::get_temp_sensor(){
  return mTempSensor;
}

