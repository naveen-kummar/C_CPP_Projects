#ifndef CRUISE_CONTROL_ROS_HEADER_TOPIC_INFO_H
#define CRUISE_CONTROL_ROS_HEADER_TOPIC_INFO_H
#include <string>

template <typename T>
class TopicInfo
{
public: 
	TopicInfo(const std::string name, const std::size_t size):
		topic_name_{ name }, queue_size_{ size }
	{

	}
	~TopicInfo() = default;
	TopicInfo(const TopicInfo&) = default;
	TopicInfo& operator=(const TopicInfo&) = default;

	inline GetTopicName()
	{
		return topic_name_;
	}

	inline T GetQueueSize()
	{
		return queue_size_;
	}

private:
	std::string  topic_name_;
	std::size_t queue_size_;

};
#endif // CRUISE_CONTROL_ROS_HEADER_TOPIC_INFO_H

