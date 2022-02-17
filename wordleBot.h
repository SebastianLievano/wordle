#pragma once
#include "wordList.h"






class wordleBot{
    private:
        wordList* words;
        sortedWords potentialWordsMap;
        vector<double> proportionalimp;
        vector<int> potentialAnswers;
        vector<inpId> bestMovesForInfo;
        int turnCounter;
        unordered_map < char, int > numWordsWLetter;
        int numRemainingAnswers;
    public:
        //Constructor
        wordleBot(wordList* wordList);
        //Destructor
        ~wordleBot();

        //Accessor
        vector<ansId> getPotentialAnswers();

        vector<pair <inpId, double > > getBestInputs();

        //Input Receiving and Update Processes
        void updatePotentialAnswers(int result[5], string word);

        //Update vector based on result (remove grays)
        void updateBasedOnGrays(int result[5], string word, vector<ansId> &vect);

        //Vector function that returns a vector of all values that are only in the frist
        vector<int> onlyInFirst(vector<int> firstVect, vector<int> secondVect);

        //Updates word map to only contain potential answers
        void updateWordMap();

        //Bot Processes
        
        //Top level returns 10 best info moves and their values
        vector< pair <inpId, double > > returnBestInfoMove();

        //Returns value of word
        double wordValue(string word);

        //Returns value of a permutation
        double permutationValue(int result[5], string word);

        //Calculates average size change based on which letters are removed
        double graysProbabilityCut(int result[5], string word);

        //Updates given vector based on green values in result
        void updateBasedOnGreens(int result[5], string word, vector<ansId> &vect);

        //Updates given vector based on yellow values
        void updateBasedOnYellows(int result[5], string word, vector<ansId> &vect);

        //returns a vector of all options in both vectors
        vector<int> inBoth(const vector<int> &answerVector, const vector<int> &wordVector);        
        //Utility
        
};

