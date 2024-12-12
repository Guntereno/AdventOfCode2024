#include "Days/Day.h"

#include <cstddef>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace
{
	enum class ParsingResult
	{
		INVALID = -1,

		CONTINUE,
		FAILED,
		SUCCESS
	};

	enum class ParsingState
	{
		COMMAND,
		ARG1,
		ARG2,
		NARG
	};

	enum class Command
	{
		INVALID = -1,

		MUL,
		DO,
		DONT
	};

	bool is_numeric(char ch)
	{
		return (ch >= '0') && (ch <= '9');
	}

	const std::vector<const char*> commands =
	{
		"mul",
		"do",
		"don't"
	};


	// Checks whether the current parsing could belong to a valid command
	bool command_parsing_valid(const std::string& str)
	{
		for (int cmd = 0; cmd < commands.size(); ++cmd)
		{
			bool is_valid = true;
			for (int ch = 0; ch < str.length(); ++ch)
			{
				if (str[ch] != commands[cmd][ch])
				{
					is_valid = false;
					break;
				}
			}

			if (is_valid)
			{
				return true;
			}
		}

		return false;
	}

	// Convert a complete parsing result to a command enum
	Command parse_command(const std::string& str)
	{
		for (int i = 0; i < commands.size(); ++i)
		{
			if (str == commands[i])
			{
				return (Command)i;
			}
		}

		return Command::INVALID;
	}


	// Maintains state for parsing an argument from a stream of characters
	class ArgParser
	{
	public:
		void reset(char terminator)
		{
			_terminator = terminator;
			_buffer = "";
			_result = ParsingResult::CONTINUE;
		}

		ParsingResult parse_char(char ch)
		{
			if (is_numeric(ch))
			{
				_buffer.push_back(ch);
			}
			else if (ch == _terminator)
			{
				_result = ParsingResult::SUCCESS;
			}
			else
			{
				_result = ParsingResult::FAILED;
			}
			return _result;
		}

		int arg()
		{
			if (_result != ParsingResult::SUCCESS)
			{
				throw std::runtime_error("Unhandled result!");
			}

			return std::stoi(_buffer);
		}

	private:
		char _terminator = '\0';
		std::string _buffer = "";
		ParsingResult _result = ParsingResult::INVALID;
	};



	// Maintains state for parsing a command from a stream of characters
	class CommandParser
	{
	public:
		ParsingResult parse_char(char ch)
		{
			_result = ParsingResult::CONTINUE;

			switch (_parsing_state)
			{
			case ParsingState::COMMAND:
				if (ch == '(')
				{
					_command = parse_command(_buffer);
					switch (_command)
					{
					case Command::MUL:
						reset(ParsingState::ARG1, TERMINATOR_ARG_SEPARATOR);
						break;

					case Command::DO:
					case Command::DONT:
						reset(ParsingState::NARG, TERMINATOR_ARGS);
						break;

					case Command::INVALID:
						reset();
						break;

					default:
						throw std::runtime_error("Unhandled Command!");
					}
				}
				else
				{
					_buffer.push_back(ch);

					if (!command_parsing_valid(_buffer))
					{
						reset();
					}
				}
				break;

			case ParsingState::ARG1:
			{
				switch (_arg_parser.parse_char(ch))
				{
				case ParsingResult::CONTINUE:
					// Do nothing
					break;

				case ParsingResult::FAILED:
					reset();
					break;

				case ParsingResult::SUCCESS:
					_arg1 = _arg_parser.arg();
					reset(ParsingState::ARG2, TERMINATOR_ARGS);
					break;

				default:
					throw std::runtime_error("Unhandled result!");
				}
				break;
			}

			case ParsingState::ARG2:
			{
				switch (_arg_parser.parse_char(ch))
				{
				case ParsingResult::CONTINUE:
					// Do nothing
					break;

				case ParsingResult::FAILED:
					reset();
					_result = ParsingResult::FAILED;
					break;

				case ParsingResult::SUCCESS:
					_arg2 = _arg_parser.arg();
					reset();
					_result = ParsingResult::SUCCESS;
					break;

				default:
					throw std::runtime_error("Unhandled result!");
				}
				break;
			}

			case ParsingState::NARG:
			{
				if (ch == ')')
				{
					_result = ParsingResult::SUCCESS;
				}
				else
				{
					_result = ParsingResult::FAILED;
					reset();
				}
				break;
			}

			default:
				throw std::runtime_error("Unhandled ParsingState!");
			}

			return _result;
		}

		void cmd(Command& out_command, int& out_arg1, int& out_arg2)
		{
			if (_result != ParsingResult::SUCCESS)
			{
				throw std::runtime_error("Unhandled result!");
			}

			out_command = _command;
			out_arg1 = _arg1;
			out_arg2 = _arg2;
		}


	private:
		static constexpr char TERMINATOR_ARG_SEPARATOR = ',';
		static constexpr char TERMINATOR_ARGS = ')';

		void reset(ParsingState parsing_state = ParsingState::COMMAND, char terminator = TERMINATOR_ARG_SEPARATOR)
		{
			_parsing_state = parsing_state;
			_arg_parser.reset(terminator);
			_buffer = "";
		}

		ParsingState _parsing_state = ParsingState::COMMAND;
		ArgParser _arg_parser;

		std::string _buffer = "";
		Command _command = Command::INVALID;

		int _arg1 = -1;
		int _arg2 = -1;

		ParsingResult _result = ParsingResult::FAILED;
	};
}


Day03::Day03()
{
	std::ifstream file_stream("Data/Day03.txt");
	if (!file_stream.is_open())
	{
		throw std::runtime_error("Failed to open file!");
	}

	char ch;
	int total_part1 = 0;
	int total_part2 = 0;
	bool do_flag = true;

	CommandParser command_parser;
	while (file_stream.get(ch))
	{
		ParsingResult result = command_parser.parse_char(ch);
		if (result == ParsingResult::SUCCESS)
		{
			Command command;
			int arg1, arg2;
			command_parser.cmd(command, arg1, arg2);

			switch (command)
			{
			case Command::MUL:
			{
				int mul = arg1 * arg2;
				total_part1 += mul;
				if (do_flag)
				{
					total_part2 += mul;
				}

				std::cout << "mul(" << arg1 << ", " << arg2 << ")" << std::endl;
				break;
			}

			case Command::DO:
				do_flag = true;
				break;

			case Command::DONT:
				do_flag = false;
				break;

			case Command::INVALID:
			default:
				throw std::runtime_error("Unhandled command!");
			}
		}
	}

	_answer1 = std::to_string(total_part1);
	_answer2 = std::to_string(total_part2);
}
