#include "Days/Day01.h"

#include <algorithm>
#include <array>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <map>
#include <vector>

Day01::Day01()
{
	std::ifstream file_stream("Data/Day01.txt");
	if (!file_stream.is_open())
	{
		throw std::runtime_error("Failed to open file!");
	}

	constexpr size_t kNumLists = 2;
	std::array<std::vector<int>, kNumLists> location_lists{ std::vector<int>(), std::vector<int>() };

	std::map<int, int> frequency_map;

	std::string line;
	while (std::getline(file_stream, line))
	{
		std::istringstream line_stream(line);
		std::string entry_str;
		int list_index = 0;
		while (line_stream >> entry_str)
		{
			int val = std::stoi(entry_str);
			location_lists[list_index].push_back(val);
			
			// Frequency map is built using the numbers in the second column
			if (list_index == 1)
			{
				auto frequency_entry = frequency_map.find(val);
				if (frequency_entry == frequency_map.end())
				{
					frequency_map.emplace(val, 1);
				}
				else
				{
					++(frequency_entry->second);
				}
			}

			++list_index;
		}
	}

	for (auto& list : location_lists)
	{
		std::sort(list.begin(), list.end());
	}

	int total_error = 0;
	int total_similarity = 0;
	for (size_t i = 0; i < location_lists[0].size(); ++i)
	{
		int a = location_lists[0][i];
		int b = location_lists[1][i];
		int diff = std::abs(b - a);
		total_error += diff;

		int frequency = frequency_map[a];
		int similarity = a * frequency;
		total_similarity += similarity;
	}

	_answer1 = total_error;
	_answer2 = total_similarity;
}

std::string Day01::Part1()
{
	return std::to_string(_answer1);
}

std::string Day01::Part2()
{
	return std::to_string(_answer2);
}