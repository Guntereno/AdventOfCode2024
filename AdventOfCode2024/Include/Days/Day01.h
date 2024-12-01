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
	int _answer1 = -1;
	int _answer2 = -1;
};
