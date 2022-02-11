#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <string>
using namespace std;

//two types of words in wordle

typedef int ansId;          //Answer words      
typedef int inpId;         //Valid input words
typedef unordered_map<char, vector < vector < ansId> > > sortedWords;