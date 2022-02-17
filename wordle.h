#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <string>
using namespace std;




struct result{
    string word;
    vector<char> gray;
    vector< pair<char,int> > yellow;
    vector < pair<char,int> > green;
};



unordered_map<char, vector< vector <int> > > ans;

struct wordLists{
    vector<string> answerWords;
    vector<string> validInputWords;

    unordered_map<char, vector < vector <int> > > words;
    
    void loadWordLists();
    void loadWordMap();
};




vector<int> calculateRemainingPotentialAnswer();


string calculateBestWord();
