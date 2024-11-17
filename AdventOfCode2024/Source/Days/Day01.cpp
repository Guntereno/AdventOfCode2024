#include "Days/Day01.h"

#include <fstream>
#include <sstream>


Day01::Day01()
{
	std::ifstream fileStream("Data/Day01.txt");
	if (!fileStream.is_open())
	{
		throw std::runtime_error("Failed to open file!");
	}

	char c;
	_currentFloor = 0;
	int index = 0;
	while (fileStream.get(c))
	{
		switch (c)
		{
		case '(':
			++_currentFloor;
			break;

		case ')':
			--_currentFloor;
			if ((_currentFloor < 0) && (_firstInBasement < 0))
			{
				_firstInBasement = index;
			}
			break;

		default:
			throw std::runtime_error("Invalid character!");
		}

		++index;
	}
}

std::string Day01::Part1()
{
	return std::to_string(_currentFloor);
}

std::string Day01::Part2()
{
	return std::to_string(_firstInBasement + 1);
}