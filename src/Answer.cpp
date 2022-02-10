#include "Answer.h"

CAnswer::CAnswer(std::string const& strWord)
{
    m_strWord = strWord;
    m_Color.resize(5);
    std::fill(m_Color.begin(), m_Color.end(), LeterState::GREY);
    m_RequiredLetters = GetRequiredLetters();
    m_NotPresentLetters = GetNotPressentLetters();
}

CAnswer::CAnswer(std::string const& strWord, std::string const& strColorPattern)
{
    m_strWord = strWord;
    m_Color = StrToPatternVector(strColorPattern);
    m_RequiredLetters = GetRequiredLetters();
    m_NotPresentLetters = GetNotPressentLetters();
}

std::set<char> CAnswer::GetRequiredLetters()
{

    std::set<char> required;

    for (auto i = 0; i < 5; i++) {
        if (m_Color[i] == LeterState::YELLOW or m_Color[i] == LeterState::GREEN)
            required.insert(m_strWord[i]);
    }

    return required;
}

std::set<char> CAnswer::GetNotPressentLetters()
{

    std::set<char> InvalidLetters;

    for (auto i = 0; i < 5; i++) {
        if (m_Color[i] != LeterState::GREY)
            continue;

        if (m_RequiredLetters.find(m_strWord[i]) == m_RequiredLetters.end() )
            InvalidLetters.insert(m_strWord[i]);
    }

    return InvalidLetters;
}

std::vector<LeterState>
CAnswer::ColorizeWord(std::string const& strTarget )
{
    
    // Incializo una lista para guardar los colores
    std::vector<LeterState> vtColor(5, LeterState::GREY);

    std::set<char> NotGreen;
        // Escribo las letras acertadas
    for (int i = 0; i < 5; i++) {

        // Se ha acertado la letra, escribo un verde
        if (strTarget[i] == m_strWord[i])
            vtColor[i] = LeterState::GREEN;
        // En caso contrario la guardo como letra por adivinar
        else
            NotGreen.insert(strTarget[i]);
    }

    // Escribo las letras amarillas
    for (int i = 0; i < 5; i++) {

        // Si ya lo he pintado de verde, no hago nada más
        if (vtColor[i] == LeterState::GREEN)
            continue;

        // Si aún es gris, miro si es una letra que esté en la palabra
        if (NotGreen.find(m_strWord[i]) != NotGreen.end())
            vtColor[i] = LeterState::YELLOW;
    }

    return vtColor;
}

std::vector<LeterState>
CAnswer::StrToPatternVector(std::string const& strColor)
{
    std::vector<LeterState> vtColor;

    for (auto num : strColor) {
        int value = num - '0';
        vtColor.push_back(static_cast<LeterState>(value));
    }

    return vtColor;
}
