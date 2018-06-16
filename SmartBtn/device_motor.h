#ifndef _DEVICE_MOTOR_H_
#define _DEVICE_MOTOR_H_
#include "sensor_state.h"

enum MOTOR_MODE{
	MOTOR_SHORT_PULSE = 0,
	MOTOR_LONG_PULSE,
	MOTOR_3_SHORT_PULSE
};

class DeviceMotor{
	
	private :
	SENSOR_STATE mMotor_Control;
	MOTOR_MODE mMotor_Mode;
	
	public:
	DeviceMotor();
	~DeviceMotor();
	void set_motor_control(SENSOR_STATE state);
	void set_motor_mode(MOTOR_MODE motorMode);
  SENSOR_STATE get_motor_control();
  MOTOR_MODE get_motor_mode();
	
	
};


#endif
