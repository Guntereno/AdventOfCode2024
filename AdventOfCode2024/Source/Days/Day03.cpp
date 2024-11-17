#include "Days/Day03.h"

#include <fstream>
#include <iostream>
#include <set>
#include <stdexcept>

namespace
{
	struct Point
	{
		int X = 0;
		int Y = 0;

		bool operator<(const Point& other) const
		{
			if (X == other.X)
			{
				return Y < other.Y;
			}

			return X < other.X;
		}
	};
}

Day03::Day03()
{
	std::ifstream fileStream("Data/Day03.txt");
	if (!fileStream.is_open())
	{
		throw std::runtime_error("Failed to open file!");
	}

	std::set<Point> visitedLocationsPart1;
	std::set<Point> visitedLocationsPart2;
	Point currentLocationPart1;
	Point currentLocationPart2Santa;
	Point currentLocationPart2RoboSanta;

	visitedLocationsPart1.insert(currentLocationPart1);
	visitedLocationsPart2.insert(currentLocationPart2Santa);

	bool isSanta = true;

	char c;
	int index = 0;
	while (fileStream.get(c))
	{
		Point& currentLocationPart2 = isSanta ? currentLocationPart2Santa : currentLocationPart2RoboSanta;
		isSanta = !isSanta;

		switch (c)
		{
		case '^':
			++currentLocationPart1.Y;
			++currentLocationPart2.Y;
			break;
		case '>':
			++currentLocationPart1.X;
			++currentLocationPart2.X;
			break;
		case 'v':
			--currentLocationPart1.Y;
			--currentLocationPart2.Y;
			break;
		case '<':
			--currentLocationPart1.X;
			--currentLocationPart2.X;
			break;

		default:
			throw std::runtime_error("Invalid character!");
		}

		visitedLocationsPart1.insert(currentLocationPart1);
		visitedLocationsPart2.insert(currentLocationPart2);
	}

	_visitedLocationCountPart1 = visitedLocationsPart1.size();
	_visitedLocationCountPart2 = visitedLocationsPart2.size();
}

std::string Day03::Part1()
{
	return std::to_string(_visitedLocationCountPart1);
}

std::string Day03::Part2()
{
	return std::to_string(_visitedLocationCountPart2);
}
