#ifndef CRUISE_CONTROL_APPLICATION_HEADER_CRUISE_MANAGER_H
#define CRUISE_CONTROL\APPLICATION\HEADER\CRUISE_MANAGER.H
#include <string>
#include <unordered_map>

#include "configurable_parameters.h"
#include "../../ros/header/dummy_ros_node.h"

using CRUISE_CONFIGURATION = std::unordered_map<std::string, ConfigParameters>;

class CruiseManager
{
public:
	CruiseManager() = default;
	~CruiseManager() = default;
	CruiseManager(const CruiseManager&) = default;
	CruiseManager& operator=(const CruiseManager&) = default;
	
	void ExecuteCruiseCOntrol();

private:
	std::unordered_map<std::string, ConfigParameters> ReadConfiguration(std::string xml_path);

	std::shared_ptr< Publisher<float>> CreatePublisher(std::shared_ptr<DummyRosNode> node2);

	void PublishRequiredAcceleration(const CRUISE_CONFIGURATION& config_param, 
		std::shared_ptr<DummyRosNode> node2,
		std::shared_ptr< Publisher<float>> publisher);

};
#endif //CRUISE_CONTROL\APPLICATION\HEADER\CRUISE_MANAGER.H
