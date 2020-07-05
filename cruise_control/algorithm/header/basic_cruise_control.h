#ifndef CRUISE_CONTROL_ALGORITHM_HEADER_BASIC_CRUISE_CONTROL_H
#define CRUISE_CONTROL_ALGORITHM_HEADER_BASIC_CRUISE_CONTROL_H

#include "ICruiseStartegy.h"

class BasicCruiseControl : public ICruiseStartegy
{
public: 
	BasicCruiseControl() = default;
	~BasicCruiseControl() = default;
	BasicCruiseControl(const BasicCruiseControl&) = default;
	BasicCruiseControl& operator=(const BasicCruiseControl&) = default;

	inline float GetAcceleration(float speed) override
	{
		float acceleration;
		//Acceleration calc algo
		return acceleration;
	}
};
#endif // CRUISE_CONTROL_ALGORITHM_HEADER_BASIC_CRUISE_CONTROL_H
