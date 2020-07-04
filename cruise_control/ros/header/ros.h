#ifndef CRUISE_CONTROL_ROS_HEADER_ROS_H
#define CRUISE_CONTROL_ROS_HEADER_ROS_H

class Ros
{
public:
	Ros() = default;
	~Ros() = default;
	Ros(const Ros&) = default;
	Ros& operator=(const Ros&) = default;

	virtual void Execute() = 0;
};

#endif //CRUISE_CONTROL_ROS_HEADER_ROS_H
