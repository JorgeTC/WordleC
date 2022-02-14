#include <iostream>
#include <regex>
#include <fstream>
#include "MainLoop.h"
#include "Match.h"
#include "Answer.h"
#include "StructUtils.h"
#include "ProgressBar.h"


std::set<std::string> WORDS;

void SolveWord() {

    CMatch Match;

    while (Match.POSSIBLES.size() >= 1) {
        std::cout << "Te sugerimos: " << Match.suggestion() << "\n";
        std::string strInsertedWord = AskForWord();
        std::string strColorPattern = AskForPattern();
        CAnswer answer(strInsertedWord, strColorPattern);
        Match.POSSIBLES = Match.GetPossibles(answer);
        std::cout << "Hay " << Match.POSSIBLES.size() << " candidatas:\n";
        Match.print();

    }
}

std::string AskForWord() {
    while (true) {

        std::string strUserWord;

        // Pido al usuario
        std::cout << "Palabra introducida ";
        std::cin >> strUserWord;

        // Compruebo que la palabra introducida esté aceptada por Wordle
        if (!IS_IN_SET(strUserWord, WORDS))
            continue;

        // La palabra es correcta
        return strUserWord;
    }
}

std::string AskForPattern()
{

    while (true) {

        std::string strUserPattern;

        // Pido al usuario
        std::cout << "Patron de colores ";
        std::cin >> strUserPattern;

        // Si lo introducido es válido, lo devuelvo
        if ((std::regex_match(strUserPattern, std::regex("[0-2]{5}"))))
            return strUserPattern;
    }
}

std::set<std::string> LoadValidWords()
{
    std::set<std::string> Words;
    std::string strCurrLine;

    // Abro el archivo
    std::ifstream inputFile("..\\..\\res\\list.txt");
    if (!inputFile.is_open()) {
        inputFile.open("res\\list.txt");
    }

    while (inputFile >> strCurrLine) {
        FixEncoding(&strCurrLine);
        Words.insert(strCurrLine);
    }

    inputFile.close();

    return Words;
}

void FixEncoding(std::string* strUTF8)
{
    // La ñ la codifican dos caracteres, quiero guardarla con solo uno.

    // Añado el caracter correcto
    std::replace(strUTF8->begin(), strUTF8->end(), -61, -92);
    // Elimino el cracter que me sobra
    strUTF8->erase(remove(strUTF8->begin(), strUTF8->end(), -79), strUTF8->end());

}

void WritePunctuationFile()
{
    // Abro el archivo
    std::ofstream punctuationFile("..\\..\\res\\punctuation.txt");
    if (!punctuationFile.is_open()) {
        punctuationFile.open("res\\punctuation.txt");
    }

    CMatch Match;
    int nTotalWords = WORDS.size();
    int nProgress{ 0 };

    ProgressBar bar;
    // Itero las palabras posibles
    for (auto const& word : WORDS) {
        // Escribo su puntacións
        punctuationFile << word << " " << Match.PunctuationForWord(word) << "\n";

        bar.Update(double(++nProgress) / double(nTotalWords));
    }

    punctuationFile.close();
}
