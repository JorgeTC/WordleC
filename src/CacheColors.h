#pragma once
#include <map>
#include <functional>
#include "Answer.h"

class Memorized
{
    std::map<int, int> m_map;
    std::function<int(CMatch*, CAnswer const&)> m_fn;
    CMatch* m_obj;

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
    Memorized(CMatch* obj, std::function<int(CMatch*, CAnswer const&)> _fn) {
        m_fn = _fn;
        m_obj = obj;
    };

    int operator()(CAnswer const& ans)
    {
        int key = ConvertColorsToInt(ans);
        if (m_map.count(key)) {
            return m_map[key];
        }
        return m_map[key] = m_fn(m_obj, ans);
    };
};
