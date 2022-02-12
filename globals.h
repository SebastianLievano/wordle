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
typedef unordered_map<char, vector<ansId>[5]> sortedWords;

char alpha [26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h','i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r' , 's' , 't', 'u', 'v', 'w', 'x', 'y', 'z'};
