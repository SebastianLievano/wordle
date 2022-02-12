#pragma once
#include "wordList.h"

wordList::wordList(){
    loadWordLists;
    loadWordMap;
}

void wordList::loadWordLists(){
    int i = 0;
    answerWords.resize(3000);
    validInputWords.resize(11000);
    ifstream answers("wordleAnswers.txt");
    while(!answers.eof()){
        answers >> answerWords[i];
        ++i;
    }
    ifstream inputs("wordleGuesses.txt");
    i = 0;
    while(!inputs.eof()){
        inputs >> validInputWords[i];
        ++i;
    }
    answerWords.shrink_to_fit();
    validInputWords.shrink_to_fit();
}



void wordList::loadWordMap(){
    string word;
    for(int i = 0; i < answerWords.size(); ++i){
        word = answerWords[i];
        for(int j = 0; j < 5; ++j){
            allWords[word[j]][j].push_back(i);
        }
    }
}
