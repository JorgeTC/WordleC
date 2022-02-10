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

#define IS_IN_SET(_item, _set) (_set.find(_item) != _set.end())
#define IS_SUBSET(_small,_big) (std::includes(_big.begin(), _big.end(), _small.begin(), _small.end()))