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

vector< pair < inpId, double > > wordleBot::getBestInputs(){
    if(turnCounter == 0){
        //Return some of the best guess options
        vector<pair <inpId, double > > bestFirstGuesses {make_pair(2368, 0), make_pair(11115, 0), make_pair(7564, 0), make_pair (109, 0)};
        return bestFirstGuesses;
    }
    return returnBestInfoMove(); 
}

//WordleBot
vector< pair <inpId, double > > wordleBot::returnBestInfoMove(){
    //goal is to return 10 best moves for information
    vector < pair <inpId, double> > bestInputs;
    double lowestWordValue, val;
    set< pair < double, inpId > > solution;
    auto lowestVal = solution.begin();
    for(int i = 0; i <  10; ++i){
        solution.insert(make_pair( wordValue(words -> validInputWords[i]), i));
    }
    lowestWordValue = lowestVal -> first;
    for(int i = 10; i < words -> validInputWords.size(); ++i){
        val = wordValue(words -> validInputWords[i]);
        if(val > lowestWordValue){
            solution.erase(lowestVal);
            solution.insert(make_pair(val, i));
        }
    }
    for(auto it = solution.begin(); it != solution.end(); ++it){
        bestInputs.push_back(*it);
    }
    return bestInputs;
}

double wordleBot::wordValue(string word){
//iterating through all 3^5 permutations
    int resultArray[5];
    double wordValue = 0;
    for(resultArray[0] = GRAY; resultArray[0] < 2; resultArray[0]++){
        for(resultArray[1] = GRAY; resultArray[1] < 2; resultArray[1]++){
            for(resultArray[2] = GRAY; resultArray[2] < 2; resultArray[2]++){
                for(resultArray[3] = GRAY; resultArray[3] < 2; resultArray[3]++){
                    for(resultArray[4] = GRAY; resultArray[4] < 2; resultArray[4]++){
                        wordValue += permutationValue(resultArray, word);
                    }
                }
            }
        }
    }
    return wordValue;
}

double wordleBot::permutationValue(int result[5], string word){
    double size, graysProbability;
    vector<ansId> potentialVals = potentialAnswers;
    updateBasedOnGreens(result, word, potentialVals);
    updateBasedOnYellows (result, word, potentialVals);
    size = graysProbabilityCut(result, word)*potentialVals.size();
    return size;
}

double wordleBot::graysProbabilityCut(int result[5], string word){
    double probability = 1, currentProbability;
    for(int i = 0; i < 5; ++i){
        if(result[i] == GRAY){
            currentProbability = (double)(numRemainingAnswers - numWordsWLetter[word[i]])/(double)(numRemainingAnswers);
            probability *= currentProbability;
        }
    }
    return probability;
}

void wordleBot::updateBasedOnGreens(int result[5], string word, vector<int> &vect){
    for(int i = 0; i < 5; ++i){
        if(result[i] == GREEN){
            vect = inBoth(vect, potentialWordsMap[i][word[i]]);
        }
    }
}

void wordleBot::updateBasedOnYellows(int result[5], string word, vector<int> &vect){
    for(int i = 0; i < 5; ++i){
        if(result[i] == YELLOW){
            for(int j = 0; j < 5; ++j){
                if(i == j) continue;
                vect = inBoth(vect, potentialWordsMap[j][word[i]]);
            }
        }
    }
}


//Since both vectors are sorted, we can use an algorithm to cut time down to O(n)
vector<int> wordleBot::inBoth(const vector<int> &answerVector, const vector<int> &wordVector){
    if(answerVector.size() == numRemainingAnswers) return wordVector;
    vector<int> valsInBoth;
    int i = 0, j = 0;
    while(i < answerVector.size() && j < wordVector.size()){
        if(answerVector[i] == wordVector[j]){
            valsInBoth.push_back(answerVector[i]);
        }
        else if(answerVector[i] < wordVector[j]) ++i;
        else ++j;
    }
    return valsInBoth;
}

void wordleBot::updatePotentialAnswers(int result[5], string word){
    updateBasedOnGreens(result, word, potentialAnswers);
    updateBasedOnYellows(result, word, potentialAnswers);
    updateBasedOnGrays(result, word, potentialAnswers);
    updateWordMap();
}

void wordleBot::updateBasedOnGrays(int result[5], string word, vector<ansId> &vect){
    for(int i = 0; i < 5; ++i){
        if(result[i] == GRAY){
            for(int j = 0; j < 5; ++j){
                vect = onlyInFirst(vect, potentialWordsMap[j][word[i]]);
            }
        }
    }
}

vector<int> wordleBot::onlyInFirst(vector<int> firstVect, vector<int> secondVect){
    auto it1 = firstVect.begin(), it2 = secondVect.begin();
    while(it1 != firstVect.end() && it2 != secondVect.end()){
        if(*it1 == *it2){
            firstVect.erase(it1);
            it1++;
        }
        else if(*it1 > *it2){
            it2++;
        }
        else it1++;
    }
    firstVect.shrink_to_fit();
    return firstVect;
}

void wordleBot::updateWordMap(){
    potentialWordsMap.clear();
    potentialWordsMap.resize(5);
    numWordsWLetter.clear();
    string word;
    numRemainingAnswers = potentialAnswers.size();
    for(int i = 0; i < potentialAnswers.size(); ++i){
        word = words -> answerWords[potentialAnswers[i]];
        for(int j = 0; j < 5; ++j){
            potentialWordsMap[j][word[j]].push_back(potentialAnswers[i]);
            numWordsWLetter[word[j]]++;
        }
    }
}