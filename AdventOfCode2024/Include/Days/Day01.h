#pragma once

#include "Day.h"

#include <string>

class Day01 : public Day
{
public:
	Day01();

	std::string Part1() override;
	std::string Part2() override;

	int GetIndex() override
	{
		return 1;
	}

private:
	int _currentFloor = 0;
	int _firstInBasement = -1;
};
