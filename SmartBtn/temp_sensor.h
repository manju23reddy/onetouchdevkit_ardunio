#ifndef _TEMPERATURE_SENSOR_H_
#define _TEMPERATURE_SENSOR_H_
#include "sensor_state.h"



class TempSensor{
	
	private :
	SENSOR_STATE mTemp_Control;
	float mTemp_Threshold_Low;
  float mTemp_Threshold_High;
	
	public:
	TempSensor();
	~TempSensor();
	void set_temperature_sensor_control(SENSOR_STATE state);
	void set_temperature_threshold_low(float thresholdLow);
  void set_temperature_threshold_high(float thresholdHigh);
	SENSOR_STATE get_temperature_sensor_control();
	float get_temperature_threshold_low();	
  float get_temperature_threshold_high();  
	float get_current_temperature();
	
};


#endif
