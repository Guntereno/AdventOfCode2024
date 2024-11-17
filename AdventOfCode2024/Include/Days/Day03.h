#pragma once

#include "Day.h"

#include <string>

class Day03 : public Day
{
public:
	Day03();

	std::string Part1() override;
	std::string Part2() override;

	int GetIndex() override
	{
		return 3;
	}

private:
	size_t _visitedLocationCountPart1 = 0;
	size_t _visitedLocationCountPart2 = 0;
};
