#pragma once
#include "globals.h"



struct result{
    string word;
    vector<char> gray;
    vector< pair<char,int> > yellow;
    vector < pair<char,int> > green;
};



class wordleBot{
    private:
        wordLists* words;
        sortedWords potentialWords; 
        vector<ansId> potentialMoves;
        vector<inpId> bestMovesForInfo;
        int turnCounter;
    public:
        //Constructor
        wordleBot(wordList* wordList);
        //Destructor
        ~wordleBot();

        //Accessor
        vector<ansId> getPotentialMoves();

        vector<inpId> getBestInputs();

        //Utility
        void updatePotentialAnswers(result result);

        void calculateBestInfoMove();
};

