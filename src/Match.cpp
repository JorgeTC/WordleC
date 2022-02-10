#include "Match.h"
#include "Answer.h"
#include "CacheColors.h"
#include <iostream>

CMatch::CMatch()
{
    // Copio el conjunto de palabras
    std::copy(WORDS.begin(), WORDS.end(), std::inserter(POSSIBLES, POSSIBLES.begin()));
}

std::string
CMatch::suggestion()
{
    std::string strSuggestion = "";
    int nMinPunctuation = WORDS.size();

    // Itero todas las palabras que me permite el juego
    //bar = ProgressBar()
    for (auto word : POSSIBLES) {

        // Evalúo la palabra
        int curr_punctuation = PunctuationForWord(word);


        // Si la palabra me descarta más elementos, la tomo como nueva sugerencia
        if (curr_punctuation < nMinPunctuation) {
            strSuggestion = word;
            nMinPunctuation = curr_punctuation;
        }
    }


    //bar.update((index + 1) / len(cls.possibles))

    return strSuggestion;
}

int
CMatch::PunctuationForWord(std::string const& strWord)
{

    CAnswer answer(strWord);
    int punctuation = 0;
    

    Memorized CacheCountPossibles(this, &CMatch::CountPossibles);

    // Iteremos todas las posibles respuestas
    for (auto word : POSSIBLES) {

        answer.m_Color = answer.ColorizeWord(word);
        answer.m_RequiredLetters = answer.GetRequiredLetters();
        answer.m_NotPresentLetters = answer.GetNotPressentLetters();

        punctuation += CacheCountPossibles(answer);

    }

    // Devuelvo la pyuntuación
    return punctuation;
}

int
CMatch::PunctuationForWordAndTarget(CAnswer word, std::string const& target) {
    // Coloreemos la palabra con el target actual
    word.m_Color = word.ColorizeWord(target);
    word.m_RequiredLetters = word.GetRequiredLetters();
    word.m_NotPresentLetters = word.GetNotPressentLetters();

    // Dada esa respuesta, obtengamos cuántas palabras válidas existen
    return CountPossibles(word);
}

int
CMatch::CountPossibles(CAnswer const& word)
{
    int counter{ 0 };

    for (auto possible : POSSIBLES) {
        counter += PossibleWord(possible, word);
    }

    return counter;
}

std::set<std::string>
CMatch::GetPossibles(CAnswer const& answer) {

    std::set<std::string> vtPossibles;

    for (auto possible : POSSIBLES) {
        if (PossibleWord(possible, answer)) {
            vtPossibles.insert(possible);
        }
    }

    return vtPossibles;
}

bool
CMatch::PossibleWord(std::string const& word, CAnswer const& answer)
{
    std::set<char> PressentLetters;

    for (int i = 0; i < 5; i++) {

        // Miro que la letra no esté ya prohibida
        if (IS_IN_SET(word[i], answer.m_NotPresentLetters))
            return false;

        // Miro qué me dicen los colores de la posición actual
        if (answer.m_Color[i] == LeterState::GREEN and word[i] != answer.m_strWord[i])
            return false;

        // Sé que en esta posición, la letra es incorrecta
        if (answer.m_Color[i] != LeterState::GREEN and word[i] == answer.m_strWord[i])
            return false;

        // Añado la lera actual
        PressentLetters.insert(word[i]);
    }

    return IS_SUBSET(answer.m_RequiredLetters, PressentLetters);
}

void
CMatch::print() {
    for (auto word : POSSIBLES)
        std::cout << word << "\n";
}