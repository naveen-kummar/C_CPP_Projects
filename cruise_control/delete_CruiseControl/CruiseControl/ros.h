#ifndef CRUISE_CONTROL_HEADERS_ROS_H
#define CRUISE_CONTROL_HEADERS_ROS_H

#include <queue>

class Ros
{
public:
	Ros() = default;
	~Ros() = default;
	Ros(const Ros&) = default;
	Ros& operator=(const Ros&) = default;

	virtual void Execute() = 0;
};

#endif //CRUISE_CONTROL_HEADERS_ROS_H
