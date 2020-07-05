#ifndef CRUISE_CONTROL_ROS_HEADER_DUMMY_ROS_NODE_H
#define CRUISE_CONTROL_ROS_HEADER_DUMMY_ROS_NODE_H
#include <string>
#include <functional>
#include <chrono>

template <typename T>
class DummyRosNode
{
public:
	create_subscription(std::string name, std::size_t queue_size, 
											std::function<void(T)>)
	{

	}

	create_publisher(std::string name, std::size_t queue_size)
	{

	}

	create_wall_timer(std::chrono::milliseconds ms, std::function<void(T)>)
	{

	}

};
#endif //CRUISE_CONTROL_ROS_HEADER_DUMMY_ROS_NODE_H
