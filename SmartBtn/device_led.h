#ifndef DEVICE_LED_H
#define DEVICE_LED_H
#include "sensor_state.h"

enum LED_MODE{
	BLINKING = 0,
	BREATHING
};

class DeviceLED{
	private:
	SENSOR_STATE mLED_Control;
	LED_MODE mLED_Mode;
	
	
	public:
	DeviceLED();
	void set_device_led_control(SENSOR_STATE ledState);
	void set_device_mode(LED_MODE ledMode);
	LED_MODE get_device_mode();
	SENSOR_STATE get_device_control();
	~DeviceLED();
	
	
};


#endif