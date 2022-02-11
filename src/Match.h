#pragma once
#include <set>
#include <string>
#include <algorithm>
#include <iterator>
#include "MainLoop.h"
#include "Answer.h"

class CMatch {
public:

	CMatch();

	std::set<std::string> POSSIBLES;

	std::string suggestion();
	int PunctuationForWord(std::string const& strWord);
	int PunctuationForWordAndTarget(CAnswer word, std::string const& target);

	int CountPossibles(CAnswer const& word);
	bool PossibleWord(std::string const& word, CAnswer const& answer);

	std::set<std::string> GetPossibles(CAnswer const& answer);

	void print();

private:
	;
};

