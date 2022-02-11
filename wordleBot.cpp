#include "wordleBot.h"

void loadWordLists(){
    int i = 0;
    potentialAnswers.resize(3000);
    potentialInputs.resize(11000);
    ifstream answers("wordleAnswers.txt");
    while(!answers.eof()){
        answers >> potentialAnswers[i];
        ++i;
    }
    ifstream inputs("wordleGuesses.txt");
    i = 0;
    while(!inputs.eof()){
        inputs >> potentialInputs[i];
        ++i;
    }
    potentialInputs.shrink_to_fit();
    potentialAnswers.shrink_to_fit();
}

void loadAnswerMap(){
    string word;
    unordered_set<char> letters;
    for(int i = 0; i < potentialAnswers.size(); ++i){
        word = potentialAnswers[i];
        for(int j = 0; j < 5; ++j){
            ans[word[j]][j].push_back(i);
            letters.insert(word[j]);
        }
    }
}



vector<int> calculateRemainingPotentialAnswer(vector<int> potentials, result ans){

}


string calculateBestWord(vector<int> potentialAnswers){

}

/*
Store each answer ID 5-10 times
- Once for each character in the appropriate vector <contains>
- Once for each letter its in
worst case = 10*~2500 ints = 100'000 bytes of storage

Then, the following operations will be carried out:
If letter is green, find all common words between current possibilities vector and green vector
Green Vector =place vector of that letter
If letter is yellow, find all common words between 4 other green vectors and possibilities vector
If letter is gray, find and remove all common words between that letters total vector.
Since all vectors are sorted, algorithms can be used. 

*/

/*
GAMEPLAN
TOP-LEVEL:
Create game board w. inputs and outputs
Create bots that inputs and outputs to board

FOR BOTH:
Load valid answers and guesses into vectors
- Use their indexes as IDs

FOR BOARD

Create some form of data structure that stores all potential ANSWERS based on locations of their letters
TRIE??

Iterate through all potential inputs (12k) and calculate their value in cutting down answers (2million)
*/
