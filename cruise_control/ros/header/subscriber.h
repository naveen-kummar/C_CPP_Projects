#ifndef CRUISE_CONTROL_ROS_HEADER_SUBSCRIBER_H
#define CRUISE_CONTROL_ROS_HEADER_SUBSCRIBER_H
#include <iostream>
#include <functional>
#include "topic_info.h"


template <typename T>
class Subscriber
{
public:
	Subscriber(const TopicInfo& topic, const DummyRosNode<T> node) :
		topic_data_{ topic }, node_{ node }
	{
		call_back_ = [](subscription_data.config_value)
		{std::cout << "The subscribed value = ";
		return; };
	}

private:
	const TopicInfo topic_data_;

	const DummyRosNode<T> node_

	std::function<void(const T&)> call_back_;
};

#endif // CRUISE_CONTROL_ROS_HEADER_SUBSCRIBER_H
