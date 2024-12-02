#include "Days/Day.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace
{
	enum class ChangeDirection
	{
		UNINITIALISED,
		CONSTANT,
		DECREASING,
		INCREASING
	};

	ChangeDirection get_change_direction(int prev, int cur)
	{
		if (prev == cur)
		{
			return ChangeDirection::CONSTANT;
		}

		if (prev > cur)
		{
			return ChangeDirection::DECREASING;
		}

		return ChangeDirection::INCREASING;
	}

	bool is_report_safe(const std::vector<int>& levels)
	{
		int prev_val = levels[0];

		ChangeDirection prev_direction = ChangeDirection::UNINITIALISED;
		for (int i = 1; i < levels.size(); ++i)
		{
			int cur_val = levels[i];
			if (cur_val == prev_val)
			{
				return false;
			}

			ChangeDirection current_direction = get_change_direction(prev_val, cur_val);
			if ((prev_direction != ChangeDirection::UNINITIALISED) && (current_direction != prev_direction))
			{
				return false;
			}

			int diff = std::abs(cur_val - prev_val);
			if (diff > 3)
			{
				return false;
			}

			prev_val = cur_val;
			prev_direction = current_direction;
		}

		return true;
	}

	void is_report_safe(std::string report, bool& out_safe, bool& out_safe_dampened)
	{
		int error_count = 0;

		std::istringstream report_stream(report);

		// Build the vector of levels
		std::vector<int> levels;
		std::string entry_str;
		while (report_stream >> entry_str)
		{
			levels.push_back(std::stoi(entry_str));
		}

		// Check if it's safe as-is
		bool is_safe = is_report_safe(levels);
		if (is_safe)
		{
			out_safe = out_safe_dampened = true;
			return;
		}

		// Try again, removing each index in turn
		out_safe = false;
		for (int i = 0; i < levels.size(); ++i)
		{
			std::vector<int> reduced_levels = levels;
			reduced_levels.erase(reduced_levels.begin() + i);
			bool is_safe = is_report_safe(reduced_levels, error_index);
			if (is_safe)
			{
				out_safe_dampened = true;
				return;
			}
		}

		out_safe_dampened = false;
	}
}


Day02::Day02()
{
	std::ifstream file_stream("Data/Day02.txt");
	if (!file_stream.is_open())
	{
		throw std::runtime_error("Failed to open file!");
	}

	int safe_count = 0;
	int dampened_safe_count = 0;
	std::string line;
	while (std::getline(file_stream, line))
	{
		bool is_safe, is_safe_dampened;
		is_report_safe(line, is_safe, is_safe_dampened);
		if (is_safe)
		{
			++safe_count;
		}
		if (is_safe_dampened)
		{
			++dampened_safe_count;
		}
	}

	_answer1 = std::to_string(safe_count);
	_answer2 = std::to_string(dampened_safe_count);
}
