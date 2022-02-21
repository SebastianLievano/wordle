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
typedef vector < unordered_map<char, vector <ansId> > > sortedWords;

//char alpha [26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h','i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r' , 's' , 't', 'u', 'v', 'w', 'x', 'y', 'z'};

#define GREEN 1
#define YELLOW 0
#define GRAY -1
#define DUP_NUM 6
#define TOTAL_NUM 5



