#include <fstream>
#include <sstream>

namespace Common
{
	std::string ReadFileToString(const char* filePath)
	{
		std::ifstream fileStream(filePath);
		if (!fileStream.is_open())
		{
			throw std::runtime_error("Failed to open file!");
		}

		std::stringstream buffer;
		buffer << fileStream.rdbuf();
		return buffer.str();
	}
}
