#ifndef _DEVICE_BUZZER_H_
#define _DEVICE_BUZZER_H_
#include "sensor_state.h"

enum BUZZER_MODE{
	BUZZER_SHORT_PULSE = 0,
	BUZZER_LONG_PULSE,
	BUZZER_3_SHORT_PULSE
};

class DeviceBuzzer{
	
	private :
	SENSOR_STATE mBuzzer_Control;
	BUZZER_MODE mBuzzer_Mode;
	
	public:
	DeviceBuzzer();
	~DeviceBuzzer();
	void set_buzzer_control(SENSOR_STATE state);
	void set_buzzer_mode(BUZZER_MODE buzzerMode);
	SENSOR_STATE get_buzzer_control();
	BUZZER_MODE get_buzzer_mode();
	
	
};


#endif