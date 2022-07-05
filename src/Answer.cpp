#include "Answer.h"
#include "StructUtils.h"

CAnswer::CAnswer(std::string const& strWord)
{
    m_strWord = strWord;
    m_Color.fill(LeterState::GREY);
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

std::multiset<char>
CAnswer::GetRequiredLetters()
{

    std::multiset<char> required;

    for (auto i = 0; i < 5; i++) {
        // Cada vez que aparezca la letra de un color distinto al gris
        // indica una aparición en la palabra objetivo.
        if (m_Color[i] == LeterState::YELLOW ||
            m_Color[i] == LeterState::GREEN)
            required.insert(m_strWord[i]);
    }

    return required;
}

std::set<char>
CAnswer::GetNotPressentLetters()
{

    std::set<char> InvalidLetters;

    for (auto i = 0; i < 5; i++) {
        // Si la letra es gris, la introduzco como no válida.
        // Puede ocurrir que la letra esté también en m_RequiredLetters.
        // Esto no será contradictorio, limitará el número de repeticiones de la letra.
        if (m_Color[i] == LeterState::GREY)
            InvalidLetters.insert(m_strWord[i]);
    }

    return InvalidLetters;
}

std::array<LeterState, 5>
CAnswer::ColorizeWord(std::string const& strTarget )
{
    
    // Incializo una lista para guardar los colores
    std::array<LeterState, 5> vtColor;
    vtColor.fill(LeterState::GREY);

    std::multiset<char> NotGreen;
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
        if (ExtractFromSet(m_strWord[i], NotGreen))
            vtColor[i] = LeterState::YELLOW;
    }

    return vtColor;
}

std::array<LeterState, 5>
CAnswer::StrToPatternVector(std::string const& strColor)
{
    std::array<LeterState, 5> vtColor;

    int index = 0;
    for (auto const& num : strColor) {
        int value = num - '0';
        vtColor[index++] = static_cast<LeterState>(value);
    }

    return vtColor;
}
