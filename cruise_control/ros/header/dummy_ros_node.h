#ifndef CRUISE_CONTROL_ROS_HEADER_DUMMY_ROS_NODE_H
#define CRUISE_CONTROL_ROS_HEADER_DUMMY_ROS_NODE_H
#include <string>
#include <functional>
#include <chrono>


class DummyRosNode
{
public:
	template <class T>
	T create_subscription(std::string name, std::size_t queue_size, 
											std::function<void(T)>)
	{
		return T
	}

	int create_publisher(std::string name, std::size_t queue_size)
	{
		return 0;
	}

	template <class T>
	T create_wall_timer(std::chrono::milliseconds ms, std::function<void(T)>)
	{
		return T
	}

};
#endif //CRUISE_CONTROL_ROS_HEADER_DUMMY_ROS_NODE_H
