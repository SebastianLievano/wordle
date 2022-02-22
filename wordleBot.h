#pragma once
#include "globals.h"

class wordleBot{
    private:
        vector<string> answers; //all potential answer words
        vector<string> validInputs; //all potential input words
        //map storing quantities of words with each letter
        vector<char> greens;
        unordered_map < char, int > letterFreq;
        //map storing words in each category
        vector < unordered_map <char, vector<ansId> > > ansMap;
        //vector storing all potential answers
        vector <ansId> potAns;
        int turnCounter;       //stores turn number
        int numAnswers;         //stores answer number
        int lastInput;          //Stores last input ID
    public:
        //Constructor
        wordleBot();
        //Destructor
        ~wordleBot();

        //Constructor Helper
        void initWords();

        //returns number of remaining potential words
        int getNumRemainingAnswers();

        //Returns input word from its ID
        string getInputWord(int id);

        //Returns answer word from its ID
        string getAnswerWord(int id);

        //Returns vector of some answers (max size 5)
        vector<ansId> getAnswers();

        //Deletes the first answer option
        void removeFirstAnswerOption();

        //Different behaviour on first turn
        void firstTurn();
        
        //Prints given vector
        void printVector(vector<int> &vect);

        //Returns vector of 5 best inputs
        int getBestInput();

        //Calculates score of word
        double getWordScore(inpId id);

        //Updates answer vector
        void updateAnswers(string result, string word);

        //Returns an updated result vector after dealing with duplicate letter edge cases
        string dealWithDuplicate(string result, string word, int idx1);

        //Updates based on green squares
        void updateBasedOnGreens(string result, string word);

        //updates based on yellow squares
        void updateBasedOnYellows(string result, string word);

        //updates based on gray squares
        void updateBasedOnGrays(string result, string word);

        //returns a vector of the values in both vectors
        vector<int> inBoth(const vector<int> &answerVector, const vector<int> &wordVector);       

        //returns a vector of the values only in the first vector
        vector<int> onlyInFirst(vector<int> firstVect, vector<int> secondVect);

        //Updates both map data structures
        void updateMaps();

        //Resets the bot without having to reload all data structures; useful for testing purposes
        void reset();
};

