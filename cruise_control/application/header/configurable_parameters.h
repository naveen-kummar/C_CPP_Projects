#ifndef CRUISE_CONTROL_APPLICATION_HEADER_CONFIGURABLE_PARAMETERS_H
#define CRUISE_CONTROL_APPLICATION_HEADER_CONFIGURABLE_PARAMETERS_H
#include <string>


class ConfigParameters
{
public:
	ConfigParameters() = default;
	~ConfigParameters() = default;
	ConfigParameters(const ConfigParameters&) = default;
	ConfigParameters& operator=(const ConfigParameters&) = default;

private: 
	std::string parameter_name;
	float parameter_value;

};
#endif // CRUISE_CONTROL_APPLICATION_HEADER_CONFIGURABLE_PARAMETERS_H

