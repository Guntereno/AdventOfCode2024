#pragma once

#include <string>

class Day
{
public:
	Day() = default;

	virtual std::string Part1() = 0;
	virtual std::string Part2() = 0;

	virtual int GetIndex() = 0;
};
