#ifndef CRUISE_CONTROL_ALGORITHM_HEADER_JERK_CONTROL_DECORATOR_H
#define CRUISE_CONTROL_ALGORITHM_HEADER_JERK_CONTROL_DECORATOR_H
#include "concrete_startegy_decorator.h"


class JerkControlDecorator : public ConreteDecorator
{
public:
	JerkControlDecorator(std::unique_ptr<ICruiseStartegy> decorated_algo, const float jerk) :
		ConreteDecorator(std::move(decorated_algo)), jerk_value_{jerk}
	{

	}

	~JerkControlDecorator() = default;
	JerkControlDecorator(const JerkControlDecorator&) = default;
	JerkControlDecorator& operator=(const JerkControlDecorator&) = default;

	inline float GetAcceleration(float speed) override
	{
		return ApplyJerkAlgo(algo_decorator->GetAcceleration(speed));
	}

private:
	inline float ApplyJerkAlgo(float acceleration)
	{
		float jerk_adjusted_accekleration{ acceleration };
		//Algo for adjusting jerk...
		return jerk_adjusted_accekleration;
	}

	float jerk_value_;
};
#endif
