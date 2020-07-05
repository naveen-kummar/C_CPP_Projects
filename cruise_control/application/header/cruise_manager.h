#ifndef CRUISE_CONTROL_APPLICATION_HEADER_CRUISE_MANAGER_H
#define CRUISE_CONTROL\APPLICATION\HEADER\CRUISE_MANAGER.H
#include <string>
#include <unordered_map>

#include "configurable_parameters.h"

class CruiseManager
{
public:
	CruiseManager() = default;
	~CruiseManager() = default;
	CruiseManager(const CruiseManager&) = default;
	CruiseManager& operator=(const CruiseManager&) = default;

	void ReadConfiguration(std::string xml_path);

private:

	std::unordered_map<std::string, ConfigParameters> cruise_configuration;

};
#endif //CRUISE_CONTROL\APPLICATION\HEADER\CRUISE_MANAGER.H
