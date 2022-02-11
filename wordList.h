#pragma once
#include "globals.h"

struct wordLists{
    vector<string> answerWords;
    vector<string> validInputWords;

    sortedWords allWords;
    
    void loadWordLists();
    void loadWordMap();
};