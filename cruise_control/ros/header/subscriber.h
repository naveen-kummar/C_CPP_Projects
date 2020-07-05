#ifndef CRUISE_CONTROL_ROS_HEADER_SUBSCRIBER_H
#define CRUISE_CONTROL_ROS_HEADER_SUBSCRIBER_H
#include <iostream>
#include <functional>
#include <memory>
#include "topic_info.h"


template <typename T>
class Subscriber
{
public:
	Subscriber(const TopicInfo& topic, 
				const std::shared_ptr<DummyRosNode<T>> node) :
		topic_data_{ topic }, node_{ node }
	{
		subscription_ = node_->create_subscription<T>(
			topic_data_.GetTopicName(), topic_data_.GetQueueSize(),
			std::bind(&Subscriber::topic_callback, this, _1);
	}

private:
	const TopicInfo topic_data_;

	std::shared_ptr<DummyRosNode<T>> node_;

	rclcpp::Subscription<T>::SharedPtr subscription_;

	void topic_callback(const T::SharedPtr msg) const
	{
		RCLCPP_INFO(node_->get_logger(), "I heard: '%s'", msg->data.c_str());
	}
};

#endif // CRUISE_CONTROL_ROS_HEADER_SUBSCRIBER_H
