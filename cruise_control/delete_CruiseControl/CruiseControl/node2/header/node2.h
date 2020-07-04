#ifndef  CRUISE_CONTROL_HEADERS_NODE2_H
#define CRUISE_CONTROL_HEADERS_NODE2_H
#include "ros.h"
class Node2 :
	public Ros
{
public: 
	Node2() = default;
	~Node2() = default;
	Node2(const Node2&) = default;
	Node2& operator=(const Node2&) = default;

	void Execute() override;
};
#endif // ! CRUISE_CONTROL_HEADERS_NODE2_H