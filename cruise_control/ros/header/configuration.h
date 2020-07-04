#ifndef CRUISE_CONTROL_ROS_HEADER_CONFIGURATION_H
#define CRUISE_CONTROL_ROS_HEADER_CONFIGURATION_H
#include <string>

enum class ConfigurationID
{
	VELOCITY = 0,
	ACCELERATION = 1,
	MASS = 2,
	JERK = 3
};


template <typename T>
class ConfigurationData
{
public: 
	ConfigurationData(const ConfigurationID id, const T value):
		config_id{ id },  config_value{ value }
	{

	}
	~ConfigurationData() = default;
	ConfigurationData(const ConfigurationData&) = default;
	ConfigurationData& operator=(const ConfigurationData&) = default;

	inline ConfigurationID GetId()
	{
		return config_id;
	}

	inline T GetValue()
	{
		return config_value;
	}

private:
	ConfigurationID config_id;
	T config_value;

};
#endif // CRUISE_CONTROL_ROS_HEADER_CONFIGURATION_H

