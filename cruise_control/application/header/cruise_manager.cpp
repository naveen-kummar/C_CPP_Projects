#include <memory>

#include "../header/cruise_manager.h"
#include "../../ros/header/topic_info.h"
#include "../../ros/header/subscriber.h"
#include "../../ros/header/publisher.h"
#include "../../algorithm/header/ICruiseStartegy.h"
#include "../../algorithm/header/basic_cruise_control.h"
#include "../../algorithm/header/concrete_startegy_decorator.h"
#include "../../algorithm/header/jerk_control_decorator.h"

CRUISE_CONFIGURATION CruiseManager::ReadConfiguration(std::string xml_path)
{
	//Read and update cruise_configuration from an xml file
}

void CruiseManager::ExecuteCruiseCOntrol()
{
	//Read cruise configuration data
	CRUISE_CONFIGURATION cruise_parameters = ReadConfiguration("xmlpath");

	if (cruise_parameters.size() == 0)
		return;

	//Create node2 for pub-sub
	std::shared_ptr<DummyRosNode> node2 = std::make_shared<DummyRosNode>();

	std::shared_ptr< Publisher<float>> aceelerator_publisher = 
										CreatePublisher(node2);



	PublishRequiredAcceleration(cruise_parameters, node2, aceelerator_publisher);
}

std::shared_ptr< Publisher<float>>  CruiseManager::CreatePublisher(std::shared_ptr<DummyRosNode> node2)
{
	//Create topic for publishing acceleration
	const TopicInfo topic_acceleration("acceleration", 10);

	std::chrono::milliseconds fequency;
	fequency.count = 500;

	return std::make_shared<Publisher<float>>(topic_acceleration, node2, fequency);
}

void  CruiseManager::PublishRequiredAcceleration(const CRUISE_CONFIGURATION& config_param, 
	std::shared_ptr<DummyRosNode> node2,
	std::shared_ptr< Publisher<float>> publisher)
{
	float return_acceleration{};

	//Check configured set speed avilable 
	auto speed_iter = config_param.find("SET_SPPED");
	if (speed_iter != config_param.end())
	{
		const float set_speed = speed_iter->second.GetValue();

		//Create topic for current vehicle speed 
		const TopicInfo topic_current_speed("vehicle_speed", 10);

		//Create subscriber for above topic
		std::shared_ptr< Subscriber<float>> speed_subscriber =
			std::make_shared<Subscriber<float>>(topic_current_speed, node2);

		//Start the subscribtion loop
		speed_subscriber->StartSubscribtion();

		//Create algorithim object using startegy + Decorator pattern
		std::unique_ptr<ICruiseStartegy> cruise_algo =
			std::make_unique<BasicCruiseControl>();

		while (speed_subscriber->GetValue() < set_speed)
		{
			return_acceleration =
				cruise_algo->GetAcceleration(speed_subscriber->GetValue());

			auto jerk_iter = config_param.find("JERK");
			if (jerk_iter != config_param.end())
			{
				const float jerK_value = jerk_iter->second.GetValue();

				cruise_algo =
					std::move(std::make_unique<JerkControlDecorator>(std::move(cruise_algo), jerK_value));

				return_acceleration = cruise_algo->GetAcceleration(speed_subscriber->GetValue());

				publisher->UpdateValue(return_acceleration);

				publisher->StartPublishing();
			}


		}

	}

	return;
}