#include "wordleBot.h"

//Constructor
wordleBot::wordleBot(){
    initWords();  
    potAns.resize(answers.size());
    for(int i = 0; i < answers.size(); ++i){
        potAns[i] = i;
    }
    turnCounter = 0;
    numAnswers = answers.size();  
    ansMap.resize(7);
    updateMaps();
}

//Destructor
wordleBot::~wordleBot(){}

//Initializes both word vectors from files
void wordleBot::initWords(){
    string input;
    ifstream ansFile("wordleAnswers.txt");
    while(!ansFile.eof()){
        ansFile >> input;
        if(input == "") break;
        answers.push_back(input);
    }
    ifstream inputs("wordleGuesses.txt");
    while(!inputs.eof()){
        inputs >> input;
        if(input == "") break;
        validInputs.push_back(input);
    }
}

//First turn special case
void wordleBot::firstTurn(){
    cout << "Good first inputs are:\nslate\ncrane\ntares\nadieu\n";
}

int wordleBot::getNumRemainingAnswers(){
    return numAnswers;
}

string wordleBot::getAnswerWord(int id){
    return answers[id];
}

string wordleBot::getInputWord(int id){
    return validInputs[id];
}

vector<ansId> wordleBot::getAnswers(){
    vector<ansId> ans;
    if(potAns.size() < 5){
        return potAns;
    }
    else{
        for(int i = 0; i < 5; ++i){
            ans.push_back(potAns[i]);
        }
    }
    return ans;
}


int wordleBot::getBestInput(){
    if(potAns.size() < 3){
        cout << "endgame" << endl;
        return -1;
    }
    int bestId;
    double bestScore = 0, score;
    for(int i = 0; i < validInputs.size(); ++i){
        score = getWordScore(i);
        if(score > bestScore){
            bestId = i;
            bestScore = score;
        }
    }
    return bestId;
}


//If letter in all values, letter freq = 1
//Max score = 5, min = 0
double wordleBot::getWordScore(inpId id){
    double score = 0;
    string word = getInputWord(id);
    unordered_set<char> letters;
    for(int i = 0; i < 5; ++i){
        if(!letters.count(word[i])){
            score += letterFreq[word[i]];
            letters.insert(word[i]);
        }
    }
    return score;
}

//Yellow/Yellow - Run first
//Green/Yellow - Find all words that fit this category
//Green/Black - Letter only appears once in spot
//Yellow/Black - Letter only appears once in spot
//Gray/Gray - normal stuff

string wordleBot::dealWithDuplicate(string result, string word, int idx1){
    char letter = word[idx1], val1 = result[idx1], val2;
    vector<int> ans;
    int idx2;
    for(int i = 0; i < 5; ++i){
        if(word[i] == letter){
            idx2 = i;
            val2 = result[idx2];
        }
    }
    //If either one is black, then we need to skip it
    if(val1 == 'B'){
        result[idx1] = 'S';
        goto done;
    }
    if(val2 == 'B'){
        result[idx2] = 'S';
        goto done;
    }
    if(val1 == val2){
        if(val1 == 'G') goto done;
        potAns = onlyInFirst(ansMap[DUP_NUM][letter], ansMap[idx1][letter]);
        potAns = onlyInFirst(potAns, ansMap[idx2][letter]);
        result[idx1] = 'S';
        result[idx2] = 'S';
        goto done;
    }
    else if(val1 == 'G'){
        potAns = inBoth(ansMap[DUP_NUM][letter], ansMap[idx1][letter]);
        potAns = onlyInFirst(potAns, ansMap[idx2][letter]);
    }
    else {
        potAns = inBoth(ansMap[DUP_NUM][letter], ansMap[idx2][letter]);
        potAns = onlyInFirst(potAns, ansMap[idx1][letter]);
    }
    done:
    return result;
}



void wordleBot::updateAnswers(string result, string word){
    unordered_set<char> letters;
    for(int i = 0; i < 5; ++i){
        if(letters.count(word[i])) result = dealWithDuplicate(result, word, i);
        else letters.insert(word[i]);
    }
    updateBasedOnGreens(result, word);
    updateBasedOnYellows(result, word);
    updateBasedOnGrays(result, word);
    for(int i = 0; i < 5; ++i){
        if(result[i] == 'G') greens.push_back(word[i]);
    }
}


void wordleBot::updateBasedOnGreens(string result, string word){
    for(int i = 0; i < 5; ++i){
        if(result[i] != 'G') continue;
        potAns = inBoth(potAns, ansMap[i][word[i]]);
    }
}

void wordleBot::updateBasedOnYellows(string result, string word){
    cout << "Started updating based on yellows" << endl;
    vector<vector<int> > ans;
    for(int i = 0; i < 5; ++i){
        if(result[i] != 'Y') continue;
        potAns = inBoth(potAns, ansMap[TOTAL_NUM][word[i]]);
        potAns = onlyInFirst(potAns, ansMap[i][word[i]]);
    }

}

void wordleBot::printVector(vector<int> &vect){
    for(int i = 0; i < vect.size(); ++i){
        cout << answers[vect[i]] << " ";
    }
    cout << endl;
}

void wordleBot::updateBasedOnGrays(string result, string word){
    for(int i = 0; i < 5; ++i){
        if(result[i] != 'B') continue;
        for(int j = 0; j < 5; ++j){
            potAns = onlyInFirst(potAns, ansMap[j][word[i]]);
        }
    }
}



vector<int> wordleBot::onlyInFirst(vector<int> firstVect, vector<int> secondVect){
    vector<int> ans;
    unordered_set<int> inSecond;
    for(int i = 0; i < secondVect.size(); ++i){
        inSecond.insert(secondVect[i]);
    }
    for(int j = 0; j < firstVect.size(); ++j){
        if(!inSecond.count(firstVect[j])) ans.push_back(firstVect[j]);
    }
    return ans;
}

vector<int> wordleBot::inBoth(const vector<int>  &firstVect, const vector<int> &secondVect){
    vector<int> ans;
    auto it1 = firstVect.begin();
    auto it2 = secondVect.begin();
    while(it1 != firstVect.end() && it2 != secondVect.end()){
        if(*it1 == *it2){
            ans.push_back(*it1);
            it1++;
        }
        else if(*it1 > *it2){
            it2++;
        }
        else it1++;
    }
     return ans;
} 

void wordleBot::updateMaps(){
    string word;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    char let;
    unordered_set<char> letters;
    letterFreq.clear();
    ansMap.clear();
    ansMap.resize(7);
    for(int i = 0; i < potAns.size(); ++i){
        word = answers[potAns[i]];
        letters.clear();
        for(int j = 0; j < 5; ++j){
            let = word[j];
            if(!letters.count(let)){
                letterFreq[let]++;
                letters.insert(let);
                ansMap[TOTAL_NUM][let].push_back(potAns[i]);
            }
            else ansMap[DUP_NUM][let].push_back(potAns[i]);
            ansMap[j][let].push_back(potAns[i]);
        }
    }
    for(int j = 0; j < greens.size(); ++j){
        letterFreq[greens[j]] = 0;
    }
    numAnswers = potAns.size();
    turnCounter++;
}



