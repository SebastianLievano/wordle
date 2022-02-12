#pragma once
#include "wordleBot.h"

class wordleGame
{
private:
    wordList* words;
    vector<string> validAnswerWords;
    string  currentWord;
    int turnNum;
public:
    
    wordleGame(/* args */);
    ~wordleGame();
};

wordleGame::wordleGame(/* args */)
{
}

wordleGame::~wordleGame()
{
}
