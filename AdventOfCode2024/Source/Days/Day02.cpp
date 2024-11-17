#include "Days/Day02.h"

#include <algorithm>
#include <array>
#include <fstream>
#include <sstream>

Day02::Day02()
{
	std::ifstream fileStream("Data/Day02.txt");
	if (!fileStream.is_open())
	{
		throw std::runtime_error("Failed to open file!");
	}

	std::string line;
	while (std::getline(fileStream, line))
	{
		std::array<int, 3> dims;
		std::stringstream lineStream(line);
		std::string dimStr;
		int index = 0;
		while (std::getline(lineStream, dimStr, 'x'))
		{
			dims[index] = std::stoi(dimStr);
			++index;
		}

		int faceA = dims[0] * dims[1];
		int faceB = dims[0] * dims[2];
		int faceC = dims[1] * dims[2];

		int slack = std::min(std::min(faceA, faceB), faceC);

		_requiredPaper += (2 * faceA) + (2 * faceB) + (2 * faceC) + slack;

		std::sort(dims.begin(), dims.end(), std::less<int>());
		int volume = dims[0] * dims[1] * dims[2];
		_requiredRibbon += ((dims[0] * 2) + (dims[1] * 2) + volume);
	}
}



std::string Day02::Part1()
{
	return std::to_string(_requiredPaper);
}

std::string Day02::Part2()
{
	return std::to_string(_requiredRibbon);
}