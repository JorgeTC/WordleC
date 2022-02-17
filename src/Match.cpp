#include "Match.h"
#include "Answer.h"
#include "CacheColors.h"
#include <iostream>
#include "StructUtils.h"
#include "ProgressBar.h"

CMatch::CMatch()
{
    // Copio el conjunto de palabras
    COPY_SET(WORDS, POSSIBLES);
}

void
CMatch::PrintSuggestion() {

    // Calculo la palabra sugerida
    std::string strSuggestion = suggestion();

    // Compruebo haber obtenido una palabra
    if (strSuggestion != "") {
        if (POSSIBLES.size() == 1)
            std::cout << "La respuesta es: " << strSuggestion << "\n";
        else
            std::cout << "Te sugerimos: " << strSuggestion << "\n";
    }
}

std::string
CMatch::suggestion()
{
    // Antes de hacer ningún cálculo compruebo que tenga suficientes candidatos.
    if (POSSIBLES.size() == 0) {
        return "";
    }

    // Si sólo hay uno o dos elementos devuelvo uno de ellos.
    // Cualquiera de los dos son opciones igualmente válidos.
    if (POSSIBLES.size() <= 2) {
        return *POSSIBLES.begin();
    }


    std::string strSuggestion = "";
    int nMinPunctuation = WORDS.size() * WORDS.size();
    int counter = 0;

    // Itero todas las palabras que me permite el juego
    ProgressBar bar;
    for (auto const& word : WORDS) {

        // Evalúo la palabra
        int curr_punctuation = PunctuationForWordLowerThan(word, nMinPunctuation);


        // Si la palabra me descarta más elementos, la tomo como nueva sugerencia
        if (curr_punctuation < nMinPunctuation ||
            (curr_punctuation == nMinPunctuation &&
                (!IS_IN_SET(strSuggestion, POSSIBLES) && IS_IN_SET(word, POSSIBLES)))) {
            strSuggestion = word;
            nMinPunctuation = curr_punctuation;
        }

        bar.Update(double(++counter) / double(WORDS.size()));
        std::cout << " " << strSuggestion << std::string(5, ' ');
    }

    // Limpio la última linea
    std::cout << "\r" << std::string(50, ' ') << "\r";

    return strSuggestion;
}

int
CMatch::PunctuationForWord(std::string const& strWord)
{

    CAnswer answer(strWord);
    int punctuation = 0;


    Memorized CacheCountPossibles(this, &CMatch::CountPossibles);

    // Iteremos todas las posibles respuestas
    for (auto const& word : POSSIBLES) {

        answer.m_Color = answer.ColorizeWord(word);
        answer.m_RequiredLetters = answer.GetRequiredLetters();
        answer.m_NotPresentLetters = answer.GetNotPressentLetters();

        punctuation += CacheCountPossibles(answer);

    }

    // Devuelvo la pyuntuación
    return punctuation;
}

int
CMatch::PunctuationForWordLowerThan(std::string const& strWord, int nMaxPunctuation) {

    CAnswer answer(strWord);
    int punctuation = 0;


    Memorized CacheCountPossibles(this, &CMatch::CountPossibles);

    // Iteremos todas las posibles respuestas
    for (auto const& word : POSSIBLES) {

        answer.m_Color = answer.ColorizeWord(word);
        answer.m_RequiredLetters = answer.GetRequiredLetters();
        answer.m_NotPresentLetters = answer.GetNotPressentLetters();

        punctuation += CacheCountPossibles(answer);

        // Si he superado la mejor puntuación encontrada hasta ahora, salgo del bucle
        if (punctuation > nMaxPunctuation)
            break;
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

    for (auto const& possible : POSSIBLES) {
        counter += PossibleWord(possible, word);
    }

    return counter;
}

std::set<std::string>
CMatch::GetPossibles(CAnswer const& answer) {

    std::set<std::string> vtPossibles;

    for (auto const& possible : POSSIBLES) {
        if (PossibleWord(possible, answer)) {
            vtPossibles.insert(possible);
        }
    }

    return vtPossibles;
}

bool
CMatch::PossibleWord(std::string const& word, CAnswer const& answer)
{
    std::multiset<char> PressentLetters;
    std::multiset<char> RequiredLetters;

    COPY_SET(answer.m_RequiredLetters, RequiredLetters);

    for (int i = 0; i < 5; i++) {

        // Miro qué me dicen los colores de la posición actual
        if (answer.m_Color[i] == LeterState::GREEN && word[i] != answer.m_strWord[i])
            return false;

        // Sé que en esta posición, la letra es incorrecta
        if (answer.m_Color[i] != LeterState::GREEN && word[i] == answer.m_strWord[i])
            return false;

        // Miro que la letra no está ya prohibida
        if (IS_IN_SET(word[i], answer.m_NotPresentLetters) &&
            !ExtractFromSet(word[i], RequiredLetters))
            return false;

        // Añado la lera actual
        PressentLetters.insert(word[i]);
    }

    return IS_SUBSET(answer.m_RequiredLetters, PressentLetters);
}

void
CMatch::print() {
    for (auto const& word : POSSIBLES)
        std::cout << word << "\n";
}