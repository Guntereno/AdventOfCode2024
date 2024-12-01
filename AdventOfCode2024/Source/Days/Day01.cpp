#include "Days/Day.h"

#include <assert.h>
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

	std::vector<int> list_a;
	std::vector<int> list_b;

	// Value is the frequency in which the key appears in list_b
	std::map<int, int> frequency_map;

	std::string line;
	while (std::getline(file_stream, line))
	{
		// Read each value in the line
		std::istringstream line_stream(line);
		std::string entry_str;
		int entry_index = 0;
		while (line_stream >> entry_str)
		{
			int val = std::stoi(entry_str);

			// Add the value to the correct list
			std::vector<int>& list = (entry_index == 0) ? list_a : list_b;
			list.push_back(val);
			
			// Update the entry in the frequency map
			if (entry_index == 1)
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

			++entry_index;
		}
	}

	// The list need to be sorted so we can compare the correct values for the distance calculation
	std::sort(list_a.begin(), list_a.end());
	std::sort(list_b.begin(), list_b.end());

	// Iterate through and calculate the distance and similarity for our data
	int total_distance = 0;
	int total_similarity = 0;
	assert(list_a.size() == list_b.size());
	for (size_t i = 0; i < list_a.size(); ++i)
	{
		int a = list_a[i];
		int b = list_b[i];
		int diff = std::abs(b - a);
		total_distance += diff;

		int frequency = frequency_map[a];
		int similarity = a * frequency;
		total_similarity += similarity;
	}

	_answer1 = total_distance;
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