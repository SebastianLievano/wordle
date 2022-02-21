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
    numMap.resize(7);
    ansMap.resize(5);
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
    cout << "Good first inputs are:\ncrane\ntares\nnotes\nadieu\n";
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

pair < double, int > wordleBot::getBestInput(){
    int bestId;
    double bestScore = 0, score;
    for(int i = 0; i < validInputs.size(); ++i){
        score = getWordScore(i);
        if(score > bestScore){
            bestId = i;
            bestScore = score;
        }
    }
    return make_pair(bestScore, bestId);
}

double wordleBot::getWordScore(inpId id){
    double score = 0;
    string word = validInputs[id];
    unordered_set<char> letters;
    for(int i = 0; i < 5; ++i){
        if(letters.count(word[i])){
            score += numMap[DUP_NUM][word[i]];
        }
        else{
            letters.insert(word[i]);
            score += getLetterScore(i, word[i]);
        }
    }
    score = score / numAnswers;
    return score;
}

double wordleBot::getLetterScore(int pos, char letter){
    double score = numMap[TOTAL_NUM][letter] + numMap[pos][letter];
    return score;
}

void wordleBot::updateAnswers(string result, string word){
    updateBasedOnGreens(result, word);
    updateBasedOnYellows(result, word);
    updateBasedOnGrays(result, word);
}

void wordleBot::updateBasedOnGreens(string result, string word){
    for(int i = 0; i < 5; ++i){
        if(result[i] != 'G') continue;
        potAns = inBoth(potAns, ansMap[i][word[i]]);
    }
}

void wordleBot::updateBasedOnYellows(string result, string word){
    for(int i = 0; i < 5; ++i){
        if(result[i] != 'Y') continue;
        for(int j = 0; j < 5; ++j){
            if(j == i) continue;
            potAns = inBoth(potAns, ansMap[j][word[i]]);
        }
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
    cout << "started inBoth" << endl;
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
    char let;
    unordered_set<char> letters;
    for(int i = 0; i < potAns.size(); ++i){
        word = answers[potAns[i]];
        letters.clear();
        for(int j = 0; j < 5; ++j){
            let = word[j];
            if(letters.count(let)) numMap[DUP_NUM][let]++;
            else{
                numMap[TOTAL_NUM][let]++;
                letters.insert(let);
            }
            numMap[j][let]++;
            ansMap[j][let].push_back(potAns[i]);
        }
    }
    numAnswers = potAns.size();
    turnCounter++;
}



