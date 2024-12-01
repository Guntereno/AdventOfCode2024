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
    std::string Part1() override;                           \
    std::string Part2() override;                           \
                                                            \
    int GetIndex() override                                 \
    {                                                       \
        return N;                                           \
    }                                                       \
                                                            \
private:                                                    \
    int _answer1 = -1;                                      \
    int _answer2 = -1;                                      \
};


DEFINE_DAY_CLASS(01);
DEFINE_DAY_CLASS(02);
