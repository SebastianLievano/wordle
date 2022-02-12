#pragma once
#include "globals.h"

struct wordList{
    vector<string> answerWords;
    vector<string> validInputWords;

    sortedWords allWords;

    wordList();
    
    void loadWordLists();
    void loadWordMap();
};