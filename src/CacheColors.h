#pragma once
#include <map>
#include <functional>
#include "Answer.h"

template<class Ret, class... Args>
class Memorized
{
    std::map<int, int> m_map;
    std::function<Ret(Args...)> fn;

    int ConvertColorsToInt(CAnswer const& ans) {

        int nTotalSum = 0;
        int nBase = 1;

        for (auto color : ans.m_Color) {
            nTotalSum += static_cast<int>(color) * nBase;
            nBase *= 3;
        }

        return nTotalSum;
    };

public:
    Memorized(std::function<Ret(Args...)> _fn) : fn(_fn) {};

    Ret operator()(Args... args)
    {
        int key = ConvertColorsToInt(args[0]);
        if (m_map.count(key)) {
            return m_map[key]
        }
        return m_map[key] = fn(args...);
    }
}

auto fn = Memorized([](int x)->int { return x + 1; });