#include "MainLoop.h"
#include <windows.h>

int main(){

    SetConsoleOutputCP(CP_UTF8);
    // SetConsoleCP(CP_UTF8);

    WORDS = LoadValidWords();

    SolveWord();

    return 0;
}