#ifndef CRUISE_CONTROL_ALGORITHM_HEADER_CRUISE_ALGO_FACTORY_H
#define CRUISE_CONTROL_ALGORITHM_HEADER_CRUISE_ALGO_FACTORY_H

#include "basic_cruise_control.h"
#include "concrete_startegy_decorator.h"
#include "jerk_control_decorator.h"
#include "../../application/header/configurable_parameters.h"

class CruiseAlgoFactory
{
public:
	static std::unique_ptr<ICruiseStartegy> CreateCruiseAlgo(const CRUISE_CONFIGURATION& config_param)
	{
		std::unique_ptr<ICruiseStartegy> cruise_algo_output{};

		//Check configured set speed avilable 
		auto speed_iter = config_param.find("SET_SPPED");
		if (speed_iter != config_param.end())
		{
			const float set_speed = speed_iter->second.GetValue();

			cruise_algo_output =
				std::make_unique<BasicCruiseControl>();
		}

		auto jerk_iter = config_param.find("JERK");
		if (jerk_iter != config_param.end())
		{
			const float jerK_value = jerk_iter->second.GetValue();

			cruise_algo_output =
				std::move(std::make_unique<JerkControlDecorator>(std::move(cruise_algo_output), jerK_value));

		}

		return std::move(cruise_algo_output);
	}
};
#endif
