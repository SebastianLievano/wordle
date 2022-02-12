#pragma once
#include "wordList.h"


struct result{
    string word;
    vector<char> gray;
    vector<char> yellow;
    vector <char> green;
};



class wordleBot{
    private:
        wordList* words;
        sortedWords potentialWordsMap; 
        vector<int> potentialAnswers;
        vector<inpId> bestMovesForInfo;
        int turnCounter;
        unordered_map < char, int > numWordsWLetter;
    public:
        //Constructor
        wordleBot(wordList* wordList);
        //Destructor
        ~wordleBot();

        //Accessor
        vector<ansId> getPotentialAnswers();

        vector<inpId> getBestInputs();

        //Utility
        void updatePotentialAnswers(result result);

        void updateBasedOnGreens(vector<char> green);

        void updateBasedOnYellows(vector<char> yellow);

        void updateBasedOnGrays(vector<char> gray);

        void calculateBestInfoMove();

        vector<int> bothIn(vector<int> vector1, vector<int> vector2);

        void endgame();

        void reloadWordMap();
};

