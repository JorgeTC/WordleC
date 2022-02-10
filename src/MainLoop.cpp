#include <iostream>
#include <regex>
#include <fstream>
#include "MainLoop.h"
#include "Match.h"
#include "Answer.h"


std::set<std::string> WORDS;

void SolveWord(){

    CMatch Match;

    while (Match.POSSIBLES.size() > 1){
        std::string strInsertedWord = AskForWord();
        std::string strColorPattern = AskForPattern();
        CAnswer answer(strInsertedWord, strColorPattern);
        Match.POSSIBLES = Match.GetPossibles(answer);
        Match.print();
        std::cout << Match.suggestion();

    }
}

std::string AskForWord(){
    while (true){

        std::string strUserWord;

        // Pido al usuario
        std::cout << "Palabra introducida ";
        std::cin >> strUserWord;

        // Compruebo que la palabra introducida esté aceptada por Wordle
        if (WORDS.find(strUserWord) == WORDS.end())
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
    std::ifstream inputFile("res/list.txt");

    while (inputFile >> strCurrLine) {
        Words.insert(strCurrLine);
    }

    inputFile.close();

    return Words;
}
