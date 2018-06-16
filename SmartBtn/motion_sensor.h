#ifndef _MOTION_SENSOR_H_
#define _MOTION_SENSOR_H_
#include "sensor_state.h"


class MotionSensor{
	
	private :
	SENSOR_STATE sensor_motion_control;
	SENSOR_STATE sensor_motion_wakeup_control;
	float sensor_motion_wakeup_threshold;
	float sensor_motion_calibration_control;
		
	
	public:
	MotionSensor();
	~MotionSensor();
	void set_sensor_motion_control(SENSOR_STATE state);
	void set_sensor_motion_wakeup_control(SENSOR_STATE state);
	void set_sensor_motion_wakeup_threshold(float wakeThreshold);
	void set_sensor_motion_calibration_control(float calibrationControl);
	
	
	
};


#endif