#include <string>
#include <set>

extern std::set<std::string> WORDS;

void SolveWord();

std::string AskForWord();
std::string AskForPattern();

std::set<std::string> LoadValidWords();
void FixEncoding(std::string *strUTF8);

void WritePunctuationFile();
