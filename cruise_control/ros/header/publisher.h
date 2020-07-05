#ifndef CRUISE_CONTROL_ROS_HEADER_PUBLISHER_H
#define CRUISE_CONTROL_ROS_HEADER_PUBLISHER_H
#include <iostream>
#include <functional>
#include <memory>
#include "topic_info.h"


template <typename T>
class Publisher
{
public:
	Publisher(const TopicInfo& topic,
		const std::shared_ptr<DummyRosNode<T>> node,
		std::chrono::milliseconds freq) :
		topic_data_{ topic }, node_{ node }, value_{}
	{
		publisher_ = node_->create_publisher<T>(topic_data_.GetTopicName(), 
													topic_data_.GetQueueSize());
		timer_ = node_->create_wall_timer(
			freq, std::bind(&Publisher::timer_callback, this));
	}

	inline void UpdateValue(T value)
	{
		value_ = value;
	}

private:
	const TopicInfo topic_data_;

	std::shared_ptr<DummyRosNode<T>> node_;

	rclcpp::Publisher<T>::SharedPtr publisher_;

	T value_;

	rclcpp::TimerBase::SharedPtr timer_;

	void topic_callback()
	{
		RCLCPP_INFO(node_->get_logger(), "Publishing: '%s'", msg->data.c_str());
		publisher_->publish(value_);
	}
};

#endif // CRUISE_CONTROL_ROS_HEADER_PUBLISHER_H
