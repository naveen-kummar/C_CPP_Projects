#ifndef CRUISE_CONTROL_ROS_HEADER_ROS_QUEUE_H
#define CRUISE_CONTROL_ROS_HEADER_ROS_QUEUE_H
#include <memory>
#include <queue>

template <typename T>
class RosQueue
{
public:
	RosQueue() : DataQueue{std::make_shared<std::queue<T>>()}
	{

	}
	~RosQueue() = default;
	RosQueue(const RosQueue&) = default;
	RosQueue& operator=(const RosQueue&) = default;


	std::shared_ptr<std::queue<T>> GetDataQueue()
	{
		return DataQueue;
	}

private: 

	std::shared_ptr<std::queue<T>> DataQueue;
};
#endif
