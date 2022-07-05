#pragma once
#include "Answer.h"
#include <string>
#include <set>
#include <array>
#include "Colors.h"

class CAnswer {
public:
	CAnswer(std::string const& strWord);
	CAnswer(std::string const& strWord, std::string const& strColorPattern);

	std::multiset<char> GetRequiredLetters();
	std::set<char> GetNotPressentLetters();

	std::array<LeterState, 5> ColorizeWord(std::string const& strWord);
	std::array<LeterState, 5> StrToPatternVector(std::string const& strColor);

//private:

	std::string m_strWord;
	std::array<LeterState, 5> m_Color;
	std::multiset<char> m_RequiredLetters;
	std::set<char> m_NotPresentLetters;
	
};