#pragma once
#include "globals.h"

class wordleBot{
    private:
        vector<string> answers; //all potential answer words
        vector<string> validInputs; //all potential input words
        //map storing quantities of words with each letter
        vector < unordered_map <char, int> > numMap;
        //map storing words in each category
        vector < unordered_map <char, vector<ansId> > > ansMap;
        //vector storing all potential answers
        vector <ansId> potAns;
        int turnCounter;       //stores turn number
        int numAnswers;         //stores answer number
    public:
        //Constructor
        wordleBot();
        //Destructor
        ~wordleBot();

        //Constructor Helper
        void initWords();

        int getNumRemainingAnswers();

        string getInputWord(int id);

        string getAnswerWord(int id);

        vector<ansId> getAnswers();

        //Different behaviour on first turn
        void firstTurn();
        
        void printVector(vector<int> &vect);

        //Returns vector of 5 best inputs
        pair < double, int > getBestInput();

        //Calculates score of word
        double getWordScore(inpId id);

        //Calculates score value of letter in that position
        double getLetterScore(int pos, char letter);

        //Updates answer vector
        void updateAnswers(string result, string word);

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

        void printAnswers();
};

