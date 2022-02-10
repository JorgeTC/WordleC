#pragma once
#include <map>
#include <functional>
#include "Answer.h"

//template<typename Ret, typename... A>
class Memorized
{
    std::map<int, int> m_map;
    std::function<int(CAnswer const& ans)> m_fn;

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
    Memorized(std::function<int(const CAnswer&)> _fn) : m_fn(_fn) {};

    int operator()(CAnswer const& ans)
    {
        int key = ConvertColorsToInt(ans);
        if (m_map.count(key)) {
            return m_map[key];
        }
        return m_map[key] = m_fn(ans);
    }
};
