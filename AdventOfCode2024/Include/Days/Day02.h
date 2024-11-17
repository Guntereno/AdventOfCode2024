#pragma once

#include "Day.h"

#include <string>

class Day02 : public Day
{
public:
	Day02();

	std::string Part1() override;
	std::string Part2() override;

	int GetIndex() override
	{
		return 2;
	}

private:
	int _requiredPaper = 0;
	int _requiredRibbon = 0;
};
