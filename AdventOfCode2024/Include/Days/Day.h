#pragma once

#include <string>

class Day
{
public:
	Day() = default;

	virtual std::string Part1() = 0;
	virtual std::string Part2() = 0;

	virtual int GetIndex() = 0;
};


#define DEFINE_DAY_CLASS(N)                                 \
class Day##N : public Day                                   \
{                                                           \
public:                                                     \
    Day##N();                                               \
                                                            \
    std::string Part1() override { return _answer1; }       \
    std::string Part2() override { return _answer2; }       \
                                                            \
    int GetIndex() override                                 \
    {                                                       \
        return N;                                           \
    }                                                       \
                                                            \
private:                                                    \
    std::string _answer1 = "";                              \
    std::string _answer2 = "";                              \
};


DEFINE_DAY_CLASS(01);
DEFINE_DAY_CLASS(02);
