#ifndef DEVICE_CONFIG_H
#define DEVICE_CONFIG_H
#include "device_led.h"
#include "sensor_state.h"
#include "device_motor.h"
#include "device_buzzer.h"
#include "temp_sensor.h"

class OneTouchDevice{
	
	private:
	char* mDevice_Key;
	DeviceLED* mDevice_LED;
  DeviceMotor* mDevice_Motor;
  DeviceBuzzer* mDevice_Buzzer;
  TempSensor* mTempSensor;
  
	
	void initSensors();
	public:
	
	OneTouchDevice(const char* key);
	char* get_device_key();
	DeviceLED* get_device_led();
  DeviceMotor* get_device_motor();
  DeviceBuzzer* get_device_buzzer();
  TempSensor* get_temp_sensor();
	~OneTouchDevice();	
	
};

#endif
