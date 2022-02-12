#include "wordleBot.h"

wordleBot::wordleBot(wordList* wordList){
    string word;
    words = wordList;
    potentialWordsMap = words -> allWords;
    potentialAnswers.resize(words -> answerWords.size());
    for(int i = 0; i < words -> answerWords.size(); ++i){
        potentialAnswers[i] = i;
        word = words->answerWords[i];
        for(int i = 0; i < 5; ++i){
            numWordsWLetter[word[i]]++;
        }
    }
    turnCounter = 0;
}

//Destructor
wordleBot::~wordleBot(){}

        //Accessor
vector<ansId> wordleBot::getPotentialAnswers(){
    return potentialAnswers;
}

vector<inpId> wordleBot::getBestInputs(){
    if(turnCounter == 0){
        bestMovesForInfo.push_back()
    }
    return bestMovesForInfo;
}

//Utility
void wordleBot::updatePotentialAnswers(result result){
    updateBasedOnGreens(result.green);
    updateBasedOnYellows(result.yellow);
    updateBasedOnGrays(result.gray);
    if(potentialAnswers.size() <= 3){
        endgame();
    }
}

void wordleBot::updateBasedOnGreens(vector<char> green){
    for(int i = 0; i < green.size(); ++i){
        if(green[i] == '0') continue;
        potentialAnswers = bothIn(potentialAnswers, potentialWordsMap[green[i]][i]);
        potentialAnswers.shrink_to_fit();
    }
}

void wordleBot::updateBasedOnYellows(vector<char> yellow){
    for(int i = 0; i < 5; ++i){
        if(yellow[i] == '0') continue;
        for(int j = 0; j < 5; ++j){
            if(i == j) continue;
            potentialAnswers = bothIn(potentialAnswers, potentialWordsMap[yellow[i]][j]);
            potentialAnswers.shrink_to_fit();
        }
    }
}

void wordleBot::updateBasedOnGrays(vector<char> gray){
    for(int i = 0; i < 5; ++i){
        if(gray[i] == '0') continue;
        for(int j = 0; j < 5; ++j){
            potentialAnswers = OnlyInFirst(potentialAnswers, potentialWordsMap[gray[i]][j]);
            potentialAnswers.shrink_to_fit();
        }
    }
}

        void calculateBestInfoMove();




vector<int> calculateRemainingPotentialAnswer(vector<int> potentials, result ans){

}


void wordleBot::calculateBestInfoMove(){
    set<ansId> bestInputs;
    for(int i = 0; i < words -> validInputWords.size(); ++i){

    }

}

double wordleBot::calculateAvgSizeOfRemainingWords(string word, )

void wordleBot::reloadWordMap(){
    string word;
    potentialWordsMap.clear();
    for(int i = 0; i < potentialAnswers.size(); ++i){
        word = potentialAnswers[i];
        for(int j = 0; j < 5; ++j){
            potentialWordsMap[word[j]][j].push_back(i);
        }
    }
}

vector<int> wordleBot::bothIn(vector<int> vector1, vector<int> vector2){
    if(vector1.size() == words -> answerWords.size()) return vector2;

}

vector<int> OnlyInFirst(vector<int> vector1, vector<int> vector2){

}

void wordleBot::endgame(){
    bestMovesForInfo = potentialAnswers;
    bestMovesForInfo.shrink_to_fit();
}