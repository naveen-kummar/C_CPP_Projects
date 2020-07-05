#ifndef CRUISE_CONTROL_ALGORITHM_HEADER_ABSTRACT_STARTEGY_DECORATOR_H
#define CRUISE_CONTROL_ALGORITHM_HEADER_ABSTRACT_STARTEGY_DECORATOR_H
#include "ICruiseStartegy.h"
#include <memory>

class ConreteDecorator : public ICruiseStartegy
{

public:
	ConreteDecorator(std::unique_ptr<ICruiseStartegy> cruise_algo) 
		: algo_decorator{ std::move(cruise_algo) }
	{

	}

	~ConreteDecorator() = default;
	ConreteDecorator(const ConreteDecorator&) = default;
	ConreteDecorator& operator=(const ConreteDecorator&) = default;

	inline float GetAcceleration(float speed) override
	{
		algo_decorator->GetAcceleration(speed);
	}


protected:
	std::unique_ptr<ICruiseStartegy> algo_decorator;
};
#endif
