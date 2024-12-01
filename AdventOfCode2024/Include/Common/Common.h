#pragma once

#include <string>

#define DEFINE_DAY_CLASS(N)                                 \
class Day##N : public Day                                   \
{                                                           \
public:                                                     \
    Day##N() {}                                             \
                                                            \
    std::string Part1() override { return ""; }             \
    std::string Part2() override { return ""; }             \
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
