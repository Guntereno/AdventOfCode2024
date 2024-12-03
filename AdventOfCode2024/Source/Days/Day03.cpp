#include "Days/Day.h"

#include <cstddef>
#include <fstream>
#include <string>

namespace
{
	enum ParsingResult
	{
		CONTINUE,
		FAILED,
		SUCCESS
	};

	enum class ParsingState
	{
		COMMAND,
		ARG1,
		ARG2
	};

	bool is_numeric(char ch)
	{
		return (ch >= '0') && (ch <= '9');
	}


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
		ParsingResult _result = CONTINUE;
	};


	class CommandParser
	{
	public:
		ParsingResult parse_char(char ch)
		{
			static const std::string COMMAND = "mul(";

			_result = ParsingResult::CONTINUE;

			switch (_parsing_state)
			{
			case ParsingState::COMMAND:
				if (ch == COMMAND[_index])
				{
					++_index;
					if (_index == COMMAND.size()) // Minus the null terminator
					{
						reset(ParsingState::ARG1, TERMINATOR_ARG1);
					}
				}
				else
				{
					reset();
				}
				break;

			case ParsingState::ARG1:
			{
				ParsingResult arg_result = _arg_parser.parse_char(ch);
				switch (arg_result)
				{
				case CONTINUE:
					++_index;
					break;

				case FAILED:
					reset();
					break;

				case SUCCESS:
					on_arg1();
					reset(ParsingState::ARG2, TERMINATOR_ARG2);
					break;

				default:
					throw std::runtime_error("Unhandled result!");
				}
				break;
			}

			case ParsingState::ARG2:
			{
				ParsingResult arg_result = _arg_parser.parse_char(ch);
				switch (arg_result)
				{
				case CONTINUE:
					++_index;
					break;

				case FAILED:
					reset();
					break;

				case SUCCESS:
					on_arg2();
					reset();
					_result = ParsingResult::SUCCESS;
					break;

				default:
					throw std::runtime_error("Unhandled result!");
				}
				break;
			}

			default:
				throw std::runtime_error("Unhandled ParsingState!");
			}

			return _result;
		}

		void cmd(int& out_arg1, int& out_arg2)
		{
			if (_result != ParsingResult::SUCCESS)
			{
				throw std::runtime_error("Unhandled result!");
			}

			out_arg1 = _arg1;
			out_arg2 = _arg2;
		}


	private:
		static constexpr char TERMINATOR_ARG1 = ',';
		static constexpr char TERMINATOR_ARG2 = ')';

		void reset(ParsingState parsing_state = ParsingState::COMMAND, char terminator = TERMINATOR_ARG1)
		{
			_parsing_state = parsing_state;
			_index = 0;
			_arg_parser.reset(terminator);
		}

		void on_arg1()
		{
			_arg1 = _arg_parser.arg();
			reset(ParsingState::ARG2, TERMINATOR_ARG2);
		}

		void on_arg2()
		{
			_arg2 = _arg_parser.arg();
			reset();
		}

		ParsingState _parsing_state = ParsingState::COMMAND;
		int _index = 0;
		ArgParser _arg_parser;

		int _arg1;
		int _arg2;
		ParsingResult _result;
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
	int total = 0;
	CommandParser command_parser;
	while (file_stream.get(ch))
	{
		ParsingResult result = command_parser.parse_char(ch);
		if (result == ParsingResult::SUCCESS)
		{
			int arg1, arg2;
			command_parser.cmd(arg1, arg2);
			total += arg1 * arg2;
		}
	}

	_answer1 = std::to_string(total);
}
