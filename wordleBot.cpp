#include "wordleBot.h"

//Constructor
//Initializing various data structures and values
wordleBot::wordleBot(){
    initWords();    //Initializes word vectors from files
    potAns.resize(answers.size());  //Resizing potential answer vector
    for(int i = 0; i < answers.size(); ++i) potAns[i] = i;
    numAnswers = answers.size();  
    ansMap.resize(7);   //Resizing ansMap to initialize the 8 maps and prevent seg_faults
    updateMaps();       //Loading maps
    lastInput = -1;     //Setting last input as an inaccessible index to prevent duplicating
}

//Destructor
wordleBot::~wordleBot(){}

//Initializes both word vectors from files
void wordleBot::initWords(){
    string input;
    ifstream ansFile("wordleAnswers.txt");  //Loading answers vectors
    while(!ansFile.eof()){
        ansFile >> input;
        if(input == "") break;
        answers.push_back(input);
    }
    ifstream inputs("wordleGuesses.txt");   //Loading words vectors
    while(!inputs.eof()){
        inputs >> input;
        if(input == "") break;
        validInputs.push_back(input);
    }
}

//First turn special case
void wordleBot::firstTurn(){
    cout << "Good first inputs are:\nslate\ncrane\ncrate\nsalet\n";
}

//Removes first answer from answer vector 
void wordleBot::removeFirstAnswerOption(){
    potAns.erase(potAns.begin());
}

//Returns number of remaining answers
int wordleBot::getNumRemainingAnswers(){
    return numAnswers;
}

//Returns word from its id
string wordleBot::getAnswerWord(int id){
    return answers[id];
}

//Returns word from its id
string wordleBot::getInputWord(int id){
    return validInputs[id];
}

//Returns first 5 answers, or less
vector<ansId> wordleBot::getAnswers(){
    vector<ansId> ans;
    if(potAns.size() < 5) return potAns;
    else for(int i = 0; i < 5; ++i) ans.push_back(potAns[i]);
    return ans;
}

//Returns best input calculated
int wordleBot::getBestInput(){
    if(potAns.size() < 3) return -1;
    int bestId;     //ID of current best input
    double bestScore = 0, score;
    for(int i = 0; i < validInputs.size(); ++i){    //Finding highest score
        if(i == lastInput) continue;    //Skipping lastInput when calculating next Input
        score = getWordScore(i);
        if(score > bestScore){    
            bestId = i;
            bestScore = score;
        }
    }
    lastInput = bestId;     //Storing last Input
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

//Receives an input result string and word confirmed to have a duplicate at idx1
//Modifies string and potAns vector to deal with the duplicates
string wordleBot::dealWithDuplicate(string result, string word, int idx2){
    char letter = word[idx2], val2 = result[idx2];
    int idx1;
    //Finding the duplicate
    for(int i = 0; i < 5; ++i){ if(word[i] == letter){idx1 = i; break;}}
    char val1 = result[idx1];
    //If val2 is gray, it should just be skipped and then the algorithm can run normally
    if(val2 == 'B'){
        result[idx2] = 'S';
        return result;
    }
    if(val1 == 'B'){
        result[idx1] = 'S';
        return result;
    }
    switch (val1)
    {
    case 'G':   if(val2 == 'G') break;  //GG Case: Runs normally
                //GY Case: Run the green aspect to set potAns to all words with letter twice and letter in idx1
                potAns = inBoth(ansMap[DUP_NUM][letter], ansMap[idx1][letter]);
                potAns = onlyInFirst(potAns, ansMap[idx2][letter]);
                //result[idx1] = 'S';     //Skipping where the green was, the yellow runs normally
                break;
    case 'Y':   if(val2 == 'G'){    //YG Case: Same as GY, just inverted indexes
                    potAns = inBoth(ansMap[DUP_NUM][letter], ansMap[idx2][letter]);
                    potAns = onlyInFirst(potAns, ansMap[idx1][letter]);
                    //result[idx2] = 'S';
                    break;
                }
                //YY Case: Setting potAns to all words with letter twice, but letter is not in either index
                potAns = onlyInFirst(ansMap[DUP_NUM][letter], ansMap[idx2][letter]);    
                potAns = onlyInFirst(potAns, ansMap[idx1][letter]);
                result[idx1] = 'S'; //Skipping yellows
                result[idx2] = 'S';
                break;
    default:    result[idx1] = 'S';
    }
    return result;
}


//Updates vector of potential vectors
void wordleBot::updateAnswers(string result, string word){
    unordered_set<char> letters;    //set used for fast lookup to check duplicates
    for(int i = 0; i < 5; ++i){
        //dealing with any found duplicates
        if(letters.count(word[i])) result = dealWithDuplicate(result, word, i);
        else{
            if(result[i] == 'G') greens.push_back(word[i]);
            letters.insert(word[i]);
        }
    }
    //running updates on greens, yellows, and grays
    //Order chosen based on which one returns smallest vecotr (small to large
    updateBasedOnGreens(result, word);
    updateBasedOnYellows(result, word);
    updateBasedOnGrays(result, word);
    //Storing which letters were green
}

//Updates potential answer vector based on fed result and word
void wordleBot::updateBasedOnGreens(string result, string word){
    for(int i = 0; i < 5; ++i){
        if(result[i] != 'G') continue;
        //Turns potAns into the intersection of the current potential Answers
        //with the vector of words with that letter in that position
        potAns = inBoth(potAns, ansMap[i][word[i]]);
    }
}

//Updates potential answer vector based on fed result and word
void wordleBot::updateBasedOnYellows(string result, string word){
    vector<vector<int> > ans;
    for(int i = 0; i < 5; ++i){
        if(result[i] != 'Y') continue;
        //First we find the intersection of potAns and all words that contain the letter
        potAns = inBoth(potAns, ansMap[TOTAL_NUM][word[i]]);
        //Then subtracting the words with the letter in that position
        potAns = onlyInFirst(potAns, ansMap[i][word[i]]);
    }

}

//Prints a given vector. useful for testing
void wordleBot::printVector(vector<int> &vect){
    for(int i = 0; i < vect.size(); ++i){
        cout << answers[vect[i]] << " ";
    }
    cout << endl;
}

//Updates vector based on grays in result
void wordleBot::updateBasedOnGrays(string result, string word){
    for(int i = 0; i < 5; ++i){
        if(result[i] != 'B') continue;
        for(int j = 0; j < 5; ++j){
            potAns = onlyInFirst(potAns, ansMap[j][word[i]]);
        }
    }
}


//Vector subtraction essentially subtracts contents of second vector from first vector
vector<int> wordleBot::onlyInFirst(vector<int> firstVect, vector<int> secondVect){
    vector<int> ans;    //Answer vector
    unordered_set<int> inSecond;    //Set of all values in second vector
    for(int i = 0; i < secondVect.size(); ++i){
        inSecond.insert(secondVect[i]);
    }
    //If element is not in both vectors, it is added to answer vector
    for(int j = 0; j < firstVect.size(); ++j){
        if(!inSecond.count(firstVect[j])) ans.push_back(firstVect[j]);
    }
    return ans;
}

//Vector algorithm that finds intersection of vectors (terms in both)
vector<int> wordleBot::inBoth(const vector<int>  &firstVect, const vector<int> &secondVect){
    vector<int> ans;
    auto it1 = firstVect.begin();
    auto it2 = secondVect.begin();
    //Since both vectors are sorted, an algorithmic approach can be used
    while(it1 != firstVect.end() && it2 != secondVect.end()){
        //If value is correct, add to answer vectors
        if(*it1 == *it2){
            ans.push_back(*it1);
            it1++;
        }
        //else increase lower valued vector index
        else if(*it1 > *it2){
            it2++;
        }
        else it1++;
    }
     return ans;
} 

//Updating map after potentialAnswers has been reloaded
void wordleBot::updateMaps(){
    string word;
    char let;
    unordered_set<char> letters;
    letterFreq.clear(); //emptying letter frequency
    ansMap.clear(); //emptying and resizing ansMap back to 7 empty vectors
    ansMap.resize(7);
    for(int i = 0; i < potAns.size(); ++i){
        word = answers[potAns[i]];
        letters.clear();
        //Loading the word into each of its respective vectors based on letter pos. and freq.
        for(int j = 0; j < 5; ++j){
            let = word[j];
            //If first time, increasing letter frequency and insering into total vector
            if(!letters.count(let)){
                letterFreq[let]++;
                letters.insert(let);
                ansMap[TOTAL_NUM][let].push_back(potAns[i]);
            }
            //if second time, inserting into duplicates vector
            else ansMap[DUP_NUM][let].push_back(potAns[i]);
            //Always inserting into correct [position][letter] vector
            ansMap[j][let].push_back(potAns[i]);
        }
    }
    //Setting letter frequency of letters that are already green to 0
    //This is done because green letters appear in every remaining answer option,
    //but that information is useless as its already been gathered
    for(int j = 0; j < greens.size(); ++j){
        letterFreq[greens[j]] = 0;
    }
    numAnswers = potAns.size();
}

//Resetting bot for test suite
void wordleBot::reset(){
    potAns.resize(answers.size());
    for(int i = 0; i < answers.size(); ++i){
        potAns[i] = i;
    }
    numAnswers = answers.size();  
    ansMap.resize(7);
    greens.clear();
    updateMaps();
    lastInput = -1;
}



