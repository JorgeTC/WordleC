#pragma once
#include "Answer.h"
#include <string>
#include <set>
#include <vector>
#include "Colors.h"

class CAnswer {
public:
	CAnswer(std::string const& strWord);
	CAnswer(std::string const& strWord, std::string const& strColorPattern);

	std::multiset<char> GetRequiredLetters();
	std::set<char> GetNotPressentLetters();

	std::vector<LeterState> ColorizeWord(std::string const& strWord);
	std::vector<LeterState> StrToPatternVector(std::string const& strColor);

//private:

	std::string m_strWord;
	std::vector<LeterState> m_Color;
	std::multiset<char> m_RequiredLetters;
	std::set<char> m_NotPresentLetters;
	
};