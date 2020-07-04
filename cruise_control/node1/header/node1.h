#ifndef  CRUISE_CONTROL_NODE1_HEADER_NODE1_H
#define CRUISE_CONTROL_NODE1_HEADER_NODE1_H
#include "../../ros/header/ros.h"

class Node1 : public Ros
{
public:
	Node1() = default;
	~Node1() = default;
	Node1(const Node1&) = default;
	Node1& operator=(const Node1&) = default;

	void Execute() override;

};
#endif // CRUISE_CONTROL_NODE1_HEADER_NODE1_H



