#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "Days/Day.h"
#include "Days/Day01.h"
#include "Days/Day02.h"
#include "Days/Day03.h"

namespace
{
    using DayFactoryFunc = std::function<std::unique_ptr<Day>()>;
    using SolutionFunctionPtr = std::string(*)();

    void runSolutions(DayFactoryFunc dayFactory)
    {
        using namespace std::chrono;

        auto start = high_resolution_clock::now();

        std::unique_ptr<Day> Day = dayFactory();

        std::cout << "Day " << Day->GetIndex() << std::endl;

        std::cout << "Part 1: " << Day->Part1() << std::endl;
        std::cout << "Part 2: " << Day->Part2() << std::endl;

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);

        std::cout << "(Completed in " << duration.count() << " microseconds)" << std::endl;

        std::cout << "Day " << Day->GetIndex() << std::endl;
    }


    bool cmdOptionExists(char** begin, char** end, const std::string& option)
    {
        return std::find(begin, end, option) != end;
    }
}


int main(int argc, char* argv[])
{
    std::vector<DayFactoryFunc> Days
    {
        []() { return std::make_unique<Day01>(); },
        []() { return std::make_unique<Day02>(); },
        []() { return std::make_unique<Day03>(); }
    };

    bool runAll = cmdOptionExists(argv, argv + argc, "-a");
    
    auto start = runAll ? Days.begin() : Days.end() - 1;
    auto end = Days.end();

    for (auto iter = start; iter != end; ++iter)
    {
        runSolutions(*iter);
    }
}
